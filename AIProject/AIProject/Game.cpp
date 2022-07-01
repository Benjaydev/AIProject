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

    UIPanel* testObject = new UIPanel(200, 100, 165, 800, 0xFFFFFFFF);
    testObject->tag = "Obstacle";
    testObject->physics->SetCollider(cType::Rectangle);
    Vector2 pos = testObject->physics->GetPosition();
    testObject->physics->collider->Fit({ {pos.x, pos.y, 0}, {pos.x+testObject->sprite->GetWidth(), pos.y + testObject->sprite->GetHeight(), 0}});

    testObject->AddToGameWorld();


    //    std::cout << "hi" << std::endl;


    nodeGraph = NodeGraph();
    int cellSize = 50;
    nodeGraph.GenerateGrid(screenWidth/cellSize, screenHeight/cellSize, cellSize, "Obstacle", 0.8);

    
    Timer timer;

    

    AIObject* testAI = new AIObject();
    testAI->physics->SetPosition({ 1000, 500 });
    testAI->AIAgent->SetSpeed(200);
    testAI->AIAgent->GoToNode(nodeGraph.GetNode(1, 10));

    while (!WindowShouldClose()) {
        DeltaTime = timer.RecordNewTime();

        if (IsKeyPressed(KEY_SPACE)) {
            testAI->AIAgent->GoToNode(nodeGraph.GetNode(rand() % ((screenWidth / cellSize)-1) + 1, rand() % ((screenHeight / cellSize)-1) + 1));
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
    ClearBackground(BLACK);
    DrawFPS(0, 0);
    
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->Draw();
    }
    nodeGraph.Draw();
    EndDrawing();
}