#include "Pathfinding.h"
#include <iostream>
#include <algorithm> 
// NODE
void Pathfinding::Node::ConnectTo(Node* other, float cost)
{
    connections.push_back(Edge(other, cost));
}

Vector2 Pathfinding::Node::WorldPosition()
{
    return { (position.x + 0.5f) * parent->m_cellSize, (position.y + 0.5f) * parent->m_cellSize };
}

// NODEGRAPH
void Pathfinding::NodeGraph::Initialise(std::vector<std::string> asciiMap, int cellSize)
{
    m_cellSize = cellSize;
    const char emptySquare = '0';
     
    // assume all strings are the same length, so we'll size the map according
    // to the number of strings and the length of the first one
    m_height = asciiMap.size();
    m_width = asciiMap[0].size();

    m_nodes = new Node * [m_width * m_height];

    // loop over the strings, creating Node entries as we go
    for (int y = 0; y < m_height; y++)
    {
        std::string& line = asciiMap[y];
        // report to the use that you have a mis-matched string length
        if (line.size() != m_width) {
            std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << std::endl;
        }
        for (int x = 0; x < m_width; x++)
        {
            // get the x-th character, or return an empty node if the string         
            // isn't long enough
            char tile = x < line.size() ? line[x] : emptySquare;

            // create a node for anything but a '.' character
            m_nodes[x + m_width * y] = tile == emptySquare ? nullptr : new Node(x, y, this);
        }
    }

    // now loop over the nodes, creating connections between each node and its      
    // neighbour to the West and South on the grid. this will link up all nodes
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node)
            {
                // see if there's a node to our west, checking for array overruns      
                // first if we're on the west-most edge
                Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
                if (nodeWest)
                {
                    node->ConnectTo(nodeWest, 1); // TODO weights
                    nodeWest->ConnectTo(node, 1);
                }

                // see if there's a node south of us, checking for array index
                // overruns again
                Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
                if (nodeSouth)
                {
                    node->ConnectTo(nodeSouth, 1);
                    nodeSouth->ConnectTo(node, 1);
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
                // draw a solid block in empty squares without a navigation node
                DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
                    (int)m_cellSize - 1, (int)m_cellSize - 1, DARKGRAY);
            }
            else
            {
                // draw the connections between the node and its neighbours
                for (int i = 0; i < node->connections.size(); i++)
                {
                    Node* other = node->connections[i].target;
                    DrawLine((node->position.x + 0.5f) * m_cellSize, (node->position.y + 0.5f) * m_cellSize, (other->position.x + 0.5f) * m_cellSize, (other->position.y + 0.5f) * m_cellSize, BLUE);
                }
            }
        }
    }
}

void Pathfinding::NodeGraph::DrawPath(Pathfinding::Path path, Color lineColor)
{
    if (path.size() == 0) {
        return;
    }

    // Draw each point in path
    for (int i = 1; i < path.size(); i++)
    {
        DrawLineEx({ (path.waypoints[i]->position.x + 0.5f) * m_cellSize, (path.waypoints[i]->position.y + 0.5f) * m_cellSize }, { (path.waypoints[i - 1]->position.x + 0.5f) * m_cellSize, (path.waypoints[i - 1]->position.y + 0.5f) * m_cellSize }, 15, GREEN);
    }
    DrawCircle((path.waypoints[0]->position.x + 0.5f)* m_cellSize, (path.waypoints[0]->position.y + 0.5f)* m_cellSize, 15, PURPLE);
    DrawCircle((path.waypoints.back()->position.x + 0.5f)* m_cellSize, (path.waypoints.back()->position.y + 0.5f)* m_cellSize, 15, RED);
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
        std::sort(openList.begin(), openList.end(), less_than_Node_GScore());

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


// PATH AGENT
void Pathfinding::PathAgent::Update(float deltaTime)
{
    if (m_path.empty()) {
        return;
    }

    Vector2 diff = Vector2Subtract(m_path.waypoints[m_currentIndex+1]->WorldPosition(), m_path.waypoints[m_currentIndex]->WorldPosition());
    float dist = Vector2DotProduct(diff, diff);
    float travelDist = m_speed * deltaTime;

    float movementDist = dist - (travelDist * travelDist);

    
    
    // Just move
    if (movementDist > 0) {
        m_position = Vector2Add(m_position, Vector2MultiplyV(Vector2Normalize(diff), { travelDist, travelDist }));
    }
    else {
        m_currentIndex++;

        // Path is finished
        if (m_currentIndex == m_path.size()-1) {
            m_position = m_path.waypoints[m_currentIndex]->WorldPosition();
            m_path.setEmpty();
        }
        else {
            // Find new direction to the node that was just found
            Vector2 diff = Vector2Subtract(m_path.waypoints[m_currentIndex]->WorldPosition(), m_path.waypoints[m_currentIndex-1]->WorldPosition());
            // Go towards that node by however much the last node was overshot by
            float overshotDistance = sqrt(movementDist);
            m_position = Vector2Add(m_position, Vector2MultiplyV(Vector2Normalize(diff), { overshotDistance, overshotDistance }));
        }
    }

}

void Pathfinding::PathAgent::GoToNode(Node* node)
{
    m_position = m_currentNode->WorldPosition();
    m_path = DijkstrasGenerate(m_currentNode, node);
    m_currentIndex = 0;
}

void Pathfinding::PathAgent::Draw()
{
    DrawCircle((int)m_position.x, (int)m_position.y, 8, { 255,255,0,255 });
}
