#include "Game.h"
#include "Timer.h"
#include "AIObject.h"


std::vector<Object*> Game::objects = std::vector<Object*>();
int Game::lifetimeObjectCount = 0;
bool Game::DebugActive = false;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Start()
{
    int screenWidth = 1200;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "AI Project");

    UIPanel* testObject = new UIPanel(200, 100, 165, 700, 0x000000FF);
    testObject->tag = "Obstacle";
    testObject->physics->SetCollider(cType::Rectangle);
    Vector2 pos = testObject->physics->GetPosition();
    testObject->physics->collider->Fit({ {pos.x, pos.y, 0}, {pos.x+testObject->sprite->GetWidth(), pos.y + testObject->sprite->GetHeight(), 0}});

    testObject->AddToGameWorld();


    nodeGraph = NodeGraph();
    int cellSize = 50;
    nodeGraph.GenerateGrid(screenWidth/cellSize, screenHeight/cellSize, cellSize, "Obstacle", 0.8);

    /*
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            AIObject* testAI = new AIObject();
            testAI->physics->SetPosition({ 600 + (100.0f*j), (175.0f * i)});
            testAI->AIAgent->SetSpeed(200);
            testAI->AIAgent->GoToNode(nodeGraph.GetNode(1, 15));
        }
    }*/
    




    Timer timer;

    bool started = false;

    while (!WindowShouldClose()) {
        DeltaTime = timer.RecordNewTime();
        //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        //{
        //   Vector2 mousePos = GetMousePosition();
        //   start = graph.GetClosestNode(Vector2({ mousePos.x, mousePos.y }));
        //   if (start != nullptr) {
        //       graphPath = AStarGenerate(start, end, Pathfinding::SqrDistanceHeuristic);
        //       //agent.SetPath(graphPath);
        //       started = false;
        //   }
        //}
        //if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        //{
        //    Vector2 mousePos = GetMousePosition();
        //    end = graph.GetClosestNode(Vector2({ mousePos.x, mousePos.y }));

        //    if (end != nullptr) {
        //        graphPath = AStarGenerate(start, end, Pathfinding::SqrDistanceHeuristic);
        //        //agent.SetPath(graphPath);
        //        started = false;
        //    }
        //}

        if (IsKeyPressed(KEY_SPACE)) {
            AIObject* testAI = new AIObject();
            testAI->physics->SetPosition({ 1000, 100.0f });
            testAI->AIAgent->SetSpeed(200);
            testAI->AIAgent->GoToNode(nodeGraph.GetNode(1, 15));
        }
        
        Update();
        Draw();     
    }

    ResetGameObjects();

    CloseWindow();
}

void Game::ResetGameObjects() {

    std::vector<std::function<void()>> storeDestroy;
    // Store all objects for deletion
    for (int i = 0; i < objects.size(); i++) {
        storeDestroy.push_back(std::bind(&Object::DeleteSelf, objects[i]));
    }
    // Destroy all objects
    for (int del = 0; del < storeDestroy.size(); del++) {
        storeDestroy[del]();
    }
    storeDestroy.clear();
    storeDestroy.shrink_to_fit();
    objects.shrink_to_fit();
}


void Game::Update() {
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->Update(DeltaTime);
    }
}


void Game::Draw() {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawFPS(0, 0);
    
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->Draw();
    }
    //nodeGraph.Draw();
    EndDrawing();
}