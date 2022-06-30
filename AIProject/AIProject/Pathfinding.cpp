#include "Pathfinding.h"
#include <iostream>
#include <algorithm> 
#include "Game.h"

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

    std::vector<Node*> openList = std::vector<Node*>();
    std::vector<Node*> closedList = std::vector<Node*>();

    openList.push_back(startNode);

    Node* currentNode;

    while (!openList.empty()) {
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
        path.waypoints.insert(path.waypoints.begin(), currentNode);
        currentNode = currentNode->lastNode;
    }

    return path;
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
//void Pathfinding::NodeGraph::Initialise(std::vector<std::string> asciiMap, int cellSize)
//{
//    m_cellSize = cellSize;
//    const char emptySquare = '0';
//     
//    // assume all strings are the same length, so we'll size the map according
//    // to the number of strings and the length of the first one
//    m_height = asciiMap.size();
//    m_width = asciiMap[0].size();
//
//    m_nodes = new Node * [m_width * m_height];
//
//    // loop over the strings, creating Node entries as we go
//    for (int y = 0; y < m_height; y++)
//    {
//        std::string& line = asciiMap[y];
//        // report to the use that you have a mis-matched string length
//        if (line.size() != m_width) {
//            std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << std::endl;
//        }
//        for (int x = 0; x < m_width; x++)
//        {
//            // get the x-th character, or return an empty node if the string         
//            // isn't long enough
//            char tile = x < line.size() ? line[x] : emptySquare;
//
//            // create a node for anything but a '.' character
//            m_nodes[x + m_width * y] = tile == emptySquare ? nullptr : new Node(x, y, this);
//        }
//    }
//
//    // now loop over the nodes, creating connections between each node and its      
//    // neighbour to the West and South on the grid. this will link up all nodes
//    for (int y = 0; y < m_height; y++)
//    {
//        for (int x = 0; x < m_width; x++)
//        {
//            Node* node = GetNode(x, y);
//            if (node)
//            {
//                // see if there's a node to our west, checking for array overruns      
//                // first if we're on the west-most edge
//                Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
//                if (nodeWest)
//                {
//                    node->ConnectTo(nodeWest, 1); // TODO weights
//                    nodeWest->ConnectTo(node, 1);
//                }
//
//                // see if there's a node south of us, checking for array index
//                // overruns again
//                Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
//                if (nodeSouth)
//                {
//                    node->ConnectTo(nodeSouth, 1);
//                    nodeSouth->ConnectTo(node, 1);
//                }
//            }
//        }
//    }
//}
void Pathfinding::NodeGraph::GenerateGrid(int width, int height, int cellSize, std::string collideTag, float collideSize)
{
    m_width = width;
    m_height = height;
    m_cellSize = cellSize;
    m_nodes = new Node * [m_width * m_height];

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

            CircleCollider* gridCollider = new CircleCollider();
            gridCollider->center = WorldPos;
            gridCollider->SetDiameter(collideSize*m_cellSize);

            bool hasHit = false;

            for (int i = 0; i < collideObjects.size(); i++) {
                Hit out = Hit();
                if (collideObjects[i]->physics->collider->Overlaps(gridCollider, { 0,0,0 }, { 0,0,0 }, out)) {
                    hasHit = true;
                    break;
                }
            }

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
                    node->ConnectTo(nodeWest, 1); // TODO weights
                    nodeWest->ConnectTo(node, 1);
                }

                // See if there's a node to the south, checking for array index
                Node* nodeNorth = GetNode(x, y - 1);
                if (nodeNorth)
                {
                    node->ConnectTo(nodeNorth, 1);
                    nodeNorth->ConnectTo(node, 1);
                }

                /*
                Node* nodeNorthEast = GetNode(x+1, y-1);
                Node* nodeNorthWest = GetNode(x-1, y-1);
                
                // Diagonals
                // North east
                if (nodeNorthEast) {
                    //node->ConnectTo(nodeNorthEast, 1.4f);
                    //nodeNorthEast->ConnectTo(node, 1.4f);
                }
                
                // North west
                if (nodeNorthWest) {
                    //node->ConnectTo(nodeNorthWest, 1.4f);
                    //nodeNorthWest->ConnectTo(node, 1.4f);
                }

                */



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
                // draw a solid block in empty squares without a navigation node
                DrawCircle((int)((x+0.5) * m_cellSize), (int)((y+0.5) * m_cellSize), (int)m_cellSize / 10, RED);
            }
            else
            {
                // draw the connections between the node and its neighbours
                for (int i = 0; i < node->connections.size(); i++)
                {
                    Node* other = node->connections[i].target;
                    DrawLine((node->position.x + 0.5f) * m_cellSize, (node->position.y + 0.5f) * m_cellSize, (other->position.x + 0.5f) * m_cellSize, (other->position.y + 0.5f) * m_cellSize, BLUE);
                    DrawCircle((node->position.x + 0.5f) * m_cellSize, (node->position.y + 0.5f) * m_cellSize, m_cellSize / 10, BLUE);
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
    if (y < 0 || y >= m_width) {
        return nullptr;
    }
        
    return GetNode(x, y);
}
//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// PATH AGENT
Pathfinding::PathAgent::~PathAgent()
{
    m_currentNode = nullptr;
}
void Pathfinding::PathAgent::Update(float deltaTime)
{
    if (isFinished) {
        return;
    }

    Vector2 diff = Vector2Subtract(m_path.waypoints[m_currentIndex+1]->WorldPosition(), ownerPhysics->GetPosition());
    float dist = Vector2DotProduct(diff, diff);
    float travelDist = m_speed * deltaTime;

    float movementDist = dist - (travelDist * travelDist);

    if (movementDist > 0) {
        ownerPhysics->SetPosition(Vector2Add(ownerPhysics->GetPosition(), Vector2MultiplyV(Vector2Normalize(diff), {travelDist, travelDist})));
    }
    else {
        m_currentIndex++;

        // Path is finished
        if (m_currentIndex == m_path.size()-1) {
            ownerPhysics->SetPosition(m_path.waypoints[m_currentIndex]->WorldPosition());
            m_path.setEmpty();
            isFinished = true;
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
    // Find the start of the path that the node is on
    m_currentNode = target->parent->GetClosestNode(ownerPhysics->GetPosition());
    if (m_currentNode != nullptr) {
        m_path = AStarGenerate(m_currentNode, target);
        m_currentIndex = 0;
        isFinished = false;
    }
    
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
    for (int i = 1; i < m_path.size(); i++)
    {
        DrawLineEx({ (m_path.waypoints[i]->position.x + 0.5f) * GetParentCellSize(), (m_path.waypoints[i]->position.y + 0.5f) * GetParentCellSize() }, {(m_path.waypoints[i - 1]->position.x + 0.5f) * GetParentCellSize(), (m_path.waypoints[i - 1]->position.y + 0.5f) * GetParentCellSize() }, 10 * (GetParentCellSize() / 50), GREEN);
    }
    DrawCircle((m_path.waypoints[0]->position.x + 0.5f) * GetParentCellSize(), (m_path.waypoints[0]->position.y + 0.5f) * GetParentCellSize(), 15 * (GetParentCellSize() / 50), PURPLE);
    DrawCircle((m_path.waypoints.back()->position.x + 0.5f) * GetParentCellSize(), (m_path.waypoints.back()->position.y + 0.5f) * GetParentCellSize(), 15 * (GetParentCellSize() / 50), RED);
}
void Pathfinding::PathAgent::SetPath(Path path)
{
    if (path.empty()) {
        m_path = path;
        m_currentIndex = 0;
        isFinished = true;
        return;
    }
    m_path = path;
    ownerPhysics->SetPosition(m_path.waypoints[0]->WorldPosition());
    m_currentIndex = 0;
    isFinished = false;
}
