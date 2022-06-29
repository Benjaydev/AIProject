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

    while (!WindowShouldClose()) {
        DeltaTime = timer.RecordNewTime();
        //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        //{
        //    Vector2 mousePos = GetMousePosition();
        //    Node* check = graph.GetClosestNode(Vector2({ mousePos.x, mousePos.y }));
        //    start = graph.GetClosestNode(Vector2({ mousePos.x, mousePos.y }));
        //}
        //if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        //{
        //    Vector2 mousePos = GetMousePosition();
        //    end = graph.GetClosestNode(Vector2({ mousePos.x, mousePos.y }));
        //}
        //graphPath = DijkstrasGenerate(start, end);

        

        BeginDrawing();
        ClearBackground(WHITE);

        graph.Draw();
        graph.DrawPath(agent.GetPath(), PURPLE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            Node* check = graph.GetClosestNode(Vector2({ mousePos.x, mousePos.y }));
            agent.GoToNode(end);
        }

        agent.Update(DeltaTime);
        agent.Draw();

        EndDrawing();
    }

    CloseWindow();
}


void Game::Update() {


}


void Game::Draw() {
    
}