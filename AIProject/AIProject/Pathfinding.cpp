#include "Pathfinding.h"
#include <iostream>
#include <algorithm> 
#include "Game.h"
#include <thread>


// PATH FINDING ALGORITHMS

Pathfinding::Path Pathfinding::DijkstrasGenerate(Node* startNode, Node* endNode)
{
    if (startNode == nullptr || endNode == nullptr) {
        std::cout << "Error creating path. One or both of the supplied nodes are null." << std::endl;
        return Path();
    }
    if (startNode == endNode) {
        return Path();
    }

    startNode->gScore = 0;
    startNode->lastNode = nullptr;

    std::vector<Node*> openList = std::vector<Node*>();

    std::vector<Node*> closedList = std::vector<Node*>();

    openList.push_back(startNode);

    Node* currentNode;

    while (!openList.empty()) {
        std::make_heap(openList.begin(), openList.end(), greater_than_Node_GScore());

        currentNode = openList[0];

        if (currentNode == endNode) {
            break;
        }

        openList.erase(openList.begin());
        closedList.push_back(currentNode);

        // Search each connection for current node
        for (int c = 0; c < currentNode->connections.size(); c++) {
            Edge edge = currentNode->connections[c];
            // If edge target is not already in closed list
            if (std::find(closedList.begin(), closedList.end(), edge.target) == closedList.end()) {
                float gScore = currentNode->gScore + edge.cost;

                // If this node has not yet been visited
                if (!std::binary_search(openList.begin(), openList.end(), edge.target)) {
                    edge.target->gScore = gScore;
                    edge.target->lastNode = currentNode;
                    openList.push_back(edge.target);
                }
                // If node is already in openlist and has a valid score
                else if (gScore < edge.target->gScore) {
                    edge.target->gScore = gScore;
                    edge.target->lastNode = currentNode;
                }
            }
        }

    }

    Path path = Path();
    currentNode = endNode;

    // Backtrack and create the path
    while (currentNode != nullptr) {
        path.waypoints.insert(path.waypoints.begin(), currentNode);
        currentNode = currentNode->lastNode;
    }

    return path;
}
Pathfinding::Path Pathfinding::AStarGenerate(Node* startNode, Node* endNode, float (*heuristic)(Node*, Node*))
{
    if (startNode == nullptr || endNode == nullptr) {
        std::cout << "Error creating path. One or both of the supplied nodes are null." << std::endl;
        return Path();
    }
    if (startNode == endNode) {
        return Path();
    }

    startNode->gScore = 0;
    startNode->lastNode = nullptr;
    endNode->lastNode = nullptr;

    std::vector<Node*> openList = std::vector<Node*>();
    std::vector<Node*> closedList = std::vector<Node*>();

    openList.push_back(startNode);

    Node* currentNode;

    while (!openList.empty()) {
        // Causes errors with too many ai in scene
        std::make_heap(openList.begin(), openList.end(), greater_than_Node_FScore());

        currentNode = openList[0];

        if (currentNode == endNode) {
            break;
        }

        openList.erase(openList.begin());
        closedList.push_back(currentNode);

        // Search each connection for current node
        for (int c = 0; c < currentNode->connections.size(); c++) {
            Edge edge = currentNode->connections[c];
            // If edge target is not already in closed list
            if (std::find(closedList.begin(), closedList.end(), edge.target) == closedList.end()) {
                float gScore = currentNode->gScore + edge.cost;
                float hScore = (*heuristic)(edge.target, endNode);
                float fScore = gScore + hScore;

                // If this node has not yet been visited
                if (!std::binary_search(openList.begin(), openList.end(), edge.target)) {
                    edge.target->gScore = gScore;
                    edge.target->fScore = fScore;
                    edge.target->lastNode = currentNode;
                    openList.push_back(edge.target);

                }
                // If node is already in openlist and has a valid score
                else if (fScore < edge.target->fScore) {
                    edge.target->gScore = gScore;
                    edge.target->fScore = fScore;
                    edge.target->lastNode = currentNode;
                }
            }
        }

    }
    

    Path path = Path();
    currentNode = endNode;

    // Backtrack and create the path
    while (currentNode != nullptr) {
        currentNode = currentNode->lastNode;
        if (currentNode != nullptr) {
            path.waypoints.insert(path.waypoints.begin(), currentNode);
        }
        
        
    }

    return path;
}

Path Pathfinding::PostPathSmooth(Path path)
{
    if (path.size() == 0) {
        return path;
    }
    Path newPath = Path();
    newPath.waypoints.push_back(path.waypoints[0]);

    int k = 0;

    std::vector<Object*> collideObjects = std::vector<Object*>();
    for (int i = 0; i < Game::objects.size(); i++) {
        if (Game::objects[i]->tag == path.waypoints[0]->parent->obstacleTag && Game::objects[i]->physics->collider != nullptr) {
            collideObjects.push_back(Game::objects[i]);
        }
    }
    
    if (collideObjects.size() == 0) {
        newPath.waypoints.push_back(path.waypoints[path.size() - 1]);
        
        return newPath;
    }

    // Search each node starting from the second
    for (int i = 1; i < path.size()-1; i++) {
        // Check each collidable object
        for (int j = 0; j < collideObjects.size(); j++) {
            // Find difference between the starting node (k) and the node being checked (i+1)
            Vector2 diff = Vector2Subtract(path.waypoints[i + 1]->WorldPosition(), newPath.waypoints[k]->WorldPosition());

            // Create ray collider from start to check node
            RayCollider* ray = new RayCollider(newPath.waypoints[k]->WorldPosition(), Vector2Normalize(diff), Vector2Length(diff));
            Hit out;
           
            // If there is a collision
            if (ray->Overlaps(collideObjects[j]->physics->collider, out)) {
                // Increase the starting node
                k++;
                // Add the node before the check node (Because k cannot reach i+1, so it must keep i)
                newPath.waypoints.push_back(path.waypoints[i]);
            }
            delete ray;
            // No collision, so start node stays at same place, and the next node will be checked
        }
    }
    // Add final node
    newPath.waypoints.push_back(path.waypoints[path.size()-1]);
    return newPath;
}



//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// NODE
Pathfinding::Node::~Node()
{
    parent = nullptr;
    lastNode = nullptr;
}
void Pathfinding::Node::ConnectTo(Node* other, float cost)
{
    connections.push_back(Edge(other, cost));
}
Vector2 Pathfinding::Node::WorldPosition()
{
    return { (position.x + 0.5f) * parent->m_cellSize, (position.y + 0.5f) * parent->m_cellSize };
}
//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// NODEGRAPH
Pathfinding::NodeGraph::~NodeGraph()
{
    delete[] m_nodes;
}
void Pathfinding::NodeGraph::GenerateGrid(Vector2 dimensions, int cellSize, std::string collideTag, float collideSize)
{
    m_width = dimensions.x / cellSize;
    m_height = dimensions.y / cellSize;
    m_cellSize = cellSize;
    m_nodes = new Node * [m_width * m_height];
    obstacleTag = collideTag;

    // Find all objects that will cut the grid
    std::vector<Object*> collideObjects = std::vector<Object*>();
    for (int i = 0; i < Game::objects.size(); i++) {
        if (Game::objects[i]->tag == collideTag && Game::objects[i]->physics->collider != nullptr) {
            collideObjects.push_back(Game::objects[i]);
        }
    }


    // Create nodes for empty grid
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Vector2 WorldPos = { (x + 0.5) * m_cellSize, (y + 0.5) * m_cellSize };

            // Create collider for node
            CircleCollider* gridCollider = new CircleCollider();
            gridCollider->center = WorldPos;
            gridCollider->SetDiameter(collideSize*m_cellSize);

            bool hasHit = false;

            // Check if node collides with any object
            for (int i = 0; i < collideObjects.size(); i++) {
                Hit out = Hit();
                if (collideObjects[i]->physics->collider->Overlaps(gridCollider, { 0,0,0 }, { 0,0,0 }, out)) {
                    // If hit. No need to search for any more hits
                    hasHit = true;
                    break;
                }
            }

            // Node is null if it collidd
            m_nodes[x + m_width * y] = hasHit ? nullptr : new Node(x, y, this);

            delete gridCollider;
            
        }
    }

    // Create Connections
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node)
            {
                // See if there's a node to the west, checking for array overruns      
                Node* nodeWest = GetNode(x - 1, y);
                if (nodeWest)
                {
                    node->ConnectTo(nodeWest, D);
                    nodeWest->ConnectTo(node, D);
                }

                // See if there's a node to the north, checking for array index
                Node* nodeNorth = GetNode(x, y - 1);
                if (nodeNorth)
                {
                    node->ConnectTo(nodeNorth, D);
                    nodeNorth->ConnectTo(node, D);
                }

                if (canUseDiagonals) {
                    Node* nodeNorthEast = GetNode(x + 1, y - 1);
                    Node* nodeNorthWest = GetNode(x - 1, y - 1);

                    // Diagonals
                    // North east
                    if (nodeNorthEast) {
                        node->ConnectTo(nodeNorthEast, D2);
                        nodeNorthEast->ConnectTo(node, D2);
                    }

                    // North west
                    if (nodeNorthWest) {
                        node->ConnectTo(nodeNorthWest, D2);
                        nodeNorthWest->ConnectTo(node, D2);
                    }
                } 
            }
        }
    }


}
void Pathfinding::NodeGraph::Draw()
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
       
            Node* node = GetNode(x, y);
            if (node == nullptr)
            {
                DrawCircle((int)((x+0.5) * m_cellSize), (int)((y+0.5) * m_cellSize), (int)m_cellSize / 10, RED);
            }
            else
            {
                // Draw the connections between the node and its neighbours
                for (int i = 0; i < node->connections.size(); i++)
                {
                    Node* other = node->connections[i].target;
                    DrawLine((node->position.x + 0.5f) * m_cellSize, (node->position.y + 0.5f) * m_cellSize, (other->position.x + 0.5f) * m_cellSize, (other->position.y + 0.5f) * m_cellSize, BLUE);
                }
            }
        }
    }
}
Pathfinding::Node* Pathfinding::NodeGraph::GetClosestNode(Vector2 worldPos)
{
    int x = (int)(worldPos.x / m_cellSize);
    if (x < 0 || x >= m_width) {
        return nullptr;
    }

    int y = (int)(worldPos.y / m_cellSize);
    if (y < 0 || y >= m_height) {
        return nullptr;
    }
        
    return GetNode(x, y);
}
Node* Pathfinding::NodeGraph::GetRandomNode()
{
    Node* node = nullptr;
    while (node == nullptr)
    {
        int x = rand() % m_width;
        int y = rand() % m_height;
        node = GetNode(x, y);
    }
    return node;
}
//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// PATH AGENT
Pathfinding::PathAgent::~PathAgent()
{
    currentNode = nullptr;
}
void Pathfinding::PathAgent::Update(float deltaTime)
{
    if (hasFinishedPath || m_path.empty() || m_path.isSingle()) {
        return;
    }

    // Calculate distance to next waypoint 
    Vector2 diff = Vector2Subtract(m_path.waypoints[m_currentIndex+1]->WorldPosition(), ownerPhysics->GetPosition());
    float dist = Vector2DotProduct(diff, diff);
    float travelDist = ownerPhysics->moveSpeed * deltaTime;

    float movementDist = dist - (travelDist * travelDist);

    // Still has distance until next waypoint
    if (movementDist > 0) {
        desiredDirection = Vector2Normalize(diff);

        // Calculate the rotation to desired rotation
        if (targetRotation == 0 && rotateInDesiredDirection) {
            // Get angle to turn towards next node
            targetRotation = atan2(desiredDirection.x, desiredDirection.y) - atan2(ownerPhysics->GetFacingDirection().x, ownerPhysics->GetFacingDirection().y);

            if (targetRotation > PI) { targetRotation -= 2 * PI; }
            else if (targetRotation <= -PI) { targetRotation += 2 * PI; }

            rotatedAmount = 0;
        }
        // Rotate towards desired rotation
        rotatedAmount += targetRotation * deltaTime * turnSpeed;
        if (abs(rotatedAmount) <= abs(targetRotation) && rotateInDesiredDirection) {
            ownerPhysics->Rotate(targetRotation * deltaTime * turnSpeed);
            
        }
        // Move towards location
        else {
            ownerPhysics->AccelerateInDirection(desiredDirection);
        }

        
    }
    else {
        m_currentIndex++;
        currentNode = m_path.waypoints[m_currentIndex];

        // Get angle to turn towards next node
        targetRotation = 0;
        rotatedAmount = 0;

        // Path is finished
        if (m_currentIndex == m_path.size()-1) {
            ownerPhysics->SetPosition(m_path.waypoints[m_currentIndex]->WorldPosition());
            m_path.setEmpty();
            hasFinishedPath = true;
        }
        else {
            // Find new direction to the node that was just found
            Vector2 diff = Vector2Subtract(m_path.waypoints[m_currentIndex]->WorldPosition(), m_path.waypoints[m_currentIndex-1]->WorldPosition());
            // Go towards that node by however much the last node was overshot by
            float overshotDistance = movementDist == 0 ? 0 : sqrt(-movementDist);
            ownerPhysics->SetPosition(Vector2Add(ownerPhysics->GetPosition(), Vector2MultiplyV(Vector2Normalize(diff), { overshotDistance, overshotDistance })));
        }
    }

}
void Pathfinding::PathAgent::GoToNode(Node* target)
{
    if (target == nullptr) {
        return;
    }

    // Find the start of the path that the node is on
    currentNode = target->parent->GetClosestNode(ownerPhysics->GetPosition());
    if (currentNode != nullptr) {
        GeneratePath(currentNode, target);
    }
    
}

void Pathfinding::PathAgent::GoTo(Vector2 point)
{
    if (parentGraph == nullptr) {
        return;
    }

    Node* target = parentGraph->GetClosestNode(point);
    if (target == nullptr) {
        return;
    }

    // Find the start of the path that the node is on
    currentNode = parentGraph->GetClosestNode(ownerPhysics->GetPosition());
    if (currentNode != nullptr) {
        GeneratePath(currentNode, target);

    }
}

void Pathfinding::PathAgent::GeneratePath(Node* startNode, Node* endNode)
{
    currentlyGeneratingPath = true;

    // Generate path
    Path path = AStarGenerate(startNode, endNode);
    path = PostPathSmooth(path);

    currentlyGeneratingPath = false;

    if (path.size() == 0) {
        return;
    }

    // Assign values for path
    m_path = path;
    m_currentIndex = 0;
    hasFinishedPath = false;
}

void Pathfinding::PathAgent::GeneratePathThreaded(Node*& startNode, Node*& endNode)
{  
    // Bind the finished callback function (Will be called when path has finished generating)
    std::function<void(Path)> func = std::bind(&PathAgent::GenerationThreadFinished, this, std::placeholders::_1);
    // Call the generation function on a seperate thread
    std::thread gen(std::bind(&PathAgent::GenerationThread, this, startNode, endNode, func));
    // Detach so that it works in the background
    gen.detach();
}

// Generates path in seperate thread
void Pathfinding::PathAgent::GenerationThread(Node*& startNode, Node*& endNode, std::function<void(Path)> callbackFunction)
{
    // If agent is already generating path, queue
    for(int i = 0; currentlyGeneratingPath; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Path generation failed
        if (i >= 600) {
            callbackFunction(Path());
        }
    }

    currentlyGeneratingPath = true;

    // Generate path
    Path path = AStarGenerate(startNode, endNode);

    path = PostPathSmooth(path);

    currentlyGeneratingPath = false;
    // Call the function when finished
    callbackFunction(path);
}

// Called when generation thread has finished
void Pathfinding::PathAgent::GenerationThreadFinished(Path path)
{
    SetPath(path);
}




void Pathfinding::PathAgent::Draw()
{
    Vector2 pos = ownerPhysics->GetPosition();
    DrawCircle((int)pos.x, (int)pos.y, 8*(GetParentCellSize() / 50), ORANGE);
}
void Pathfinding::PathAgent::DrawPath()
{
    if (m_path.size() == 0) {
        return;
    }

    // Draw each point in path
    for (int i = m_currentIndex+1; i < m_path.size(); i++)
    {
        // Draw line from agent to next node 
        if (i == m_currentIndex + 1) {
            DrawLineEx({ (m_path.waypoints[i]->position.x + 0.5f) * GetParentCellSize(), (m_path.waypoints[i]->position.y + 0.5f) * GetParentCellSize() }, ownerPhysics->GetPosition(), 10 * (GetParentCellSize() / 50), GREEN);
            continue;
        }
        // Draw line from node to node
        DrawLineEx({ (m_path.waypoints[i]->position.x + 0.5f) * GetParentCellSize(), (m_path.waypoints[i]->position.y + 0.5f) * GetParentCellSize() }, {(m_path.waypoints[i - 1]->position.x + 0.5f) * GetParentCellSize(), (m_path.waypoints[i - 1]->position.y + 0.5f) * GetParentCellSize() }, 10 * (GetParentCellSize() / 50), GREEN);
    }
    // Draw end point
    DrawCircle((m_path.waypoints.back()->position.x + 0.5f) * GetParentCellSize(), (m_path.waypoints.back()->position.y + 0.5f) * GetParentCellSize(), 15 * (GetParentCellSize() / 50), RED);
}
void Pathfinding::PathAgent::SetPath(Path path)
{
    if (path.empty()) {
        m_path = path;
        m_currentIndex = 0;
        hasFinishedPath = true;
        return;
    }
    targetRotation == 0;

    m_path = path;
    //ownerPhysics->SetPosition(m_path.waypoints[0]->WorldPosition());
    m_currentIndex = 0;
    hasFinishedPath = false;
}
