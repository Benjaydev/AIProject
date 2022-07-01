#pragma once
#include "raymath.h"
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include "Object.h"


namespace Pathfinding
{
    static float D2 = sqrt(2);
    static float D = 1;

    struct Node;
    class NodeGraph;

    struct Edge {
        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _node, float _cost) : target(_node), cost(_cost) {}
        ~Edge() { target = nullptr; }
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
        ~Node();


        NodeGraph* parent;

        Vector2 position;
        std::vector<Edge> connections;
        

        float gScore;
        float fScore;
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
    };struct greater_than_Node_GScore
    {
        inline bool operator() (const Node* node1, const Node* node2)
        {
            return (node1->gScore > node2->gScore);
        }
    };
    struct less_than_Node_FScore
    {
        inline bool operator() (const Node* node1, const Node* node2)
        {
            return (node1->fScore < node2->fScore);
        }
    };
    struct greater_than_Node_FScore
    {
        inline bool operator() (const Node* node1, const Node* node2)
        {
            return (node1->fScore > node2->fScore);
        }
    };


    struct Path {
        Path() { waypoints = std::vector<Node*>(); }
        ~Path(){ waypoints.clear(); }
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
        ~NodeGraph();

        int m_width, m_height = 0;
        float m_cellSize = 0;

        Node** m_nodes;

        std::string obstacleTag = "";

        //void Initialise(std::vector<std::string> asciiMap, int cellSize);
        void GenerateGrid(int width, int height, int cellSize, std::string collideTag = "Obstacle", float collideSize = 0.9f);

        void Draw();
        void DrawPath(Path path, Color lineColor);
        Node* GetNode(int x, int y) { 
            if (x < 0 || x > m_width || y < 0 || y > m_height) {
                return nullptr;
            }
            return m_nodes[x + m_width * y];
        }
        
        Node* GetClosestNode(Vector2 worldPos);
       
    };
    static float SqrDistanceHeuristic(Node* node, Node* end) {
        Vector2 diff = Vector2Subtract(end->position, node->position);
        return Vector2DotProduct(diff, diff);
    }
    static float DistanceHeuristic(Node* node, Node* end) {
        return Vector2Distance(end->position, node->position);
    }
    static float ManhattenDistance(Node* node, Node* end) {
        float absx = abs(node->position.x - end->position.x);
        float absy = abs(node->position.y - end->position.y);
        return absx + absy;
    }
    static float DiagonalDistance(Node* node, Node* end) {
        float absx = abs(node->position.x - end->position.x);
        float absy = abs(node->position.y - end->position.y);
        return D * fmaxf(absx, absy) + (D2 - D) * fminf(absx, absy);
    }

    static float NoHeuristic(Node* node, Node* end) {
        return 0;
    }

    static float(*DefaultHeuristic)(Node*, Node*) = DiagonalDistance;


     Path DijkstrasGenerate(Node* startNode, Node* endNode);
     Path AStarGenerate(Node* startNode, Node* endNode, float (*heuristic)(Node*,Node*) = DefaultHeuristic);
        
     Path PostPathSmooth(Path path);

     



class PathAgent {
     private:
         Path m_path;
         int m_currentIndex;
         Node* m_currentNode;
         float m_speed;

         bool hasFinishedPath = true;
         bool currentlyGeneratingPath = false;


     public:

         PathAgent(PhysicsComponent* ownerPhysicsComp) {
             ownerPhysics = ownerPhysicsComp;
         }
         ~PathAgent();

         PhysicsComponent* ownerPhysics;

         void Update(float DeltaTime);
         void GoToNode(Node* target);
         void GeneratePathThreaded(Node*& startNode, Node*& endNode);
         void GenerationThread(Node*& startNode, Node*& endNode, std::function<void(Path)> callbackFunction);
         void GenerationThreadFinished(Path path);

         void Draw();
         void DrawPath();
         float GetParentCellSize() {
             return (m_path.empty() ? 50 : m_path.waypoints[0]->parent->m_cellSize);
         }

         void SetSpeed(float speed) {
             m_speed = speed;
         }
         Path GetPath() { return m_path; }
         void SetPath(Path path);

     };
};

