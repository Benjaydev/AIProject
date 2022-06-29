#pragma once
#include "raymath.h"
#include <vector>
#include <string>

namespace Pathfinding
{
    struct Node;
    struct Edge {
        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _node, float _cost) : target(_node), cost(_cost) {}

        Node* target;
        float cost;

        inline bool operator== (const Edge& other) const { return (target == other.target) && (cost == other.cost); }
    };


    struct Node {
        Node() { position = { 0, 0 }; connections = std::vector<Edge>(); }
        Node(float x, float y) { position = { x, y }; connections = std::vector<Edge>(); }

        Vector2 position;
        std::vector<Edge> connections;

        float gScore;
        Node* lastNode;

        bool equalTo(Node* other) {
            return (position.x == other->position.x) && (position.y == other->position.y);
        }
        
        inline bool operator== (const Node& other) const { return (position.x == other.position.x) && (position.y == other.position.y); }
        

    public:
        void ConnectTo(Node* other, float cost);
    };
    struct less_than_Node_GScore
    {
        inline bool operator() (const Node* node1, const Node* node2)
        {
            return (node1->gScore < node2->gScore);
        }
    };


    struct Path {
        Path() { waypoints = std::vector<Node*>(); }

        std::vector<Node*> waypoints;
    public:
        int size() { return waypoints.size(); }
    };


     class NodeGraph {
        int m_width, m_height;
        float m_cellSize;

        Node** m_nodes;

    public:
        void Initialise(std::vector<std::string> asciiMap, int cellSize);

        void Draw();
        void DrawPath(Path path, Color lineColor);
        Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }

        Node* GetClosestNode(Vector2 worldPos);

        Path DijkstrasGenerate(Node* startNode, Node* endNode);

        
    };
};

