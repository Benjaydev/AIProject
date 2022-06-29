#include "Game.h"
#include "Pathfinding.h"
#include "Timer.h"
using namespace Pathfinding;

std::vector<Object*> Game::objects = std::vector<Object*>();
int Game::lifetimeObjectCount = 0;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Start()
{
    InitWindow(1200, 800, "AI Project");

    std::vector<std::string> asciiMap;
    asciiMap.push_back("000000000000");
    asciiMap.push_back("010111011110");
    asciiMap.push_back("010111111110");
    asciiMap.push_back("011111000100");
    asciiMap.push_back("010111010110");
    asciiMap.push_back("010001010110");
    asciiMap.push_back("011111011110");
    asciiMap.push_back("000000000000");

    NodeGraph graph = NodeGraph();
    graph.Initialise(asciiMap, 100);

    Path graphPath = DijkstrasGenerate(graph.GetNode(1, 1), graph.GetNode(10, 6));

    Node* start = graph.GetNode(1, 1);
    Node* end = graph.GetNode(10, 6);

    PathAgent agent;
    agent.SetPath(graphPath);
    agent.SetSpeed(200);


    Timer timer;

    bool started = false;

    while (!WindowShouldClose()) {
        DeltaTime = timer.RecordNewTime();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           Vector2 mousePos = GetMousePosition();
           start = graph.GetClosestNode(Vector2({ mousePos.x, mousePos.y }));
           if (start != nullptr) {
               graphPath = DijkstrasGenerate(start, end);
               agent.SetPath(graphPath);
               started = false;
           }
        }
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            end = graph.GetClosestNode(Vector2({ mousePos.x, mousePos.y }));

            if (end != nullptr) {
                graphPath = DijkstrasGenerate(start, end);
                agent.SetPath(graphPath);
                started = false;
            }
        }
        
        

        BeginDrawing();
        ClearBackground(WHITE);

        graph.Draw();
        graph.DrawPath(agent.GetPath(), PURPLE);

        if (IsKeyPressed(KEY_SPACE)) {
            started = !started;
        }
        if (started) {
            agent.Update(DeltaTime);
        }
        
        agent.Draw();

        EndDrawing();
    }

    CloseWindow();
}


void Game::Update() {


}


void Game::Draw() {
    
}