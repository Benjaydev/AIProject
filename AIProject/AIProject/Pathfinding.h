#pragma once
#include "raymath.h"
#include <vector>
#include <string>
#include <iostream>

namespace Pathfinding
{
    struct Node;
    class NodeGraph;

    struct Edge {
        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _node, float _cost) : target(_node), cost(_cost) {}

        Node* target;
        float cost;

        inline bool operator== (const Edge& other) const { return (target == other.target) && (cost == other.cost); }
    };


    struct Node {
        Node() { position = { 0, 0 }; connections = std::vector<Edge>(); parent = nullptr; }
        Node(float x, float y, NodeGraph* _parent) { 
            position = { x, y };
            connections = std::vector<Edge>(); 
            parent = _parent;
        }
        NodeGraph* parent;

        Vector2 position;
        std::vector<Edge> connections;

        float gScore;
        Node* lastNode;

        

        inline bool operator== (const Node& other) const { return (position.x == other.position.x) && (position.y == other.position.y); }
        
    public:
        void ConnectTo(Node* other, float cost);

        Vector2 WorldPosition();
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
        bool empty() { return waypoints.empty(); }
        void setEmpty() {
            waypoints = std::vector<Node*>();
        }
    };


    class NodeGraph {
    public:
        int m_width, m_height;
        float m_cellSize;

        Node** m_nodes;

        void Initialise(std::vector<std::string> asciiMap, int cellSize);

        void Draw();
        void DrawPath(Path path, Color lineColor);
        Node* GetNode(int x, int y) { 
            return m_nodes[x + m_width * y];
        }
        



        Node* GetClosestNode(Vector2 worldPos);
       
    };
     Path DijkstrasGenerate(Node* startNode, Node* endNode);


     class PathAgent {
     private:
         Vector2 m_position;

         Path m_path;
         int m_currentIndex;
         Node* m_currentNode;

         float m_speed;

     public:
         void Update(float deltaTime);
         void GoToNode(Node* node);
         void Draw();
         void SetSpeed(float speed) {
             m_speed = speed;
         }
         Path GetPath() { return m_path; }
         void SetPath(Path path) {
             m_path = path;
             m_position = m_path.waypoints[0]->WorldPosition();
         }

     };
};

