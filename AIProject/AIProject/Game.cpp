#include "Game.h"
#include "Timer.h"
#include "AIObject.h"
#include "Behaviour.h"
using namespace Behaviours;


std::vector<Object*> Game::objects = std::vector<Object*>();
int Game::lifetimeObjectCount = 0;
bool Game::DebugActive = true;
Vector4 Game::WorldBorders = { 0, 0, 0, 0 };


Game::Game()
{
}

Game::~Game()
{
    delete nodeGraph;
}

void Game::Start()
{

    int screenWidth = 1200;
    int screenHeight = 800;
    WorldBorders.z = screenWidth;
    WorldBorders.w = screenHeight;

    InitWindow(screenWidth, screenHeight, "AI Project");

    UIPanel* testObject = new UIPanel(200, 100, 200, 800, 0xFFFFFFFF);
    testObject->tag = "Obstacle";
    testObject->physics->hasPhysicsCheck = true;
    testObject->physics->SetCollider(cType::Rectangle);
    Vector2 pos = testObject->physics->GetPosition();
    testObject->physics->collider->Fit({ {pos.x, pos.y, 0}, {pos.x + testObject->sprite->GetWidth(), pos.y + testObject->sprite->GetHeight(), 0} });

    testObject->AddToGameWorld();




    nodeGraph = new NodeGraph();
    int cellSize = 50;
    nodeGraph->GenerateGrid({ (float)screenWidth, (float)screenHeight }, cellSize, "Obstacle", 0.8);

    Timer timer;


    player = new Player();
    player->physics->SetPosition({ 900, 100 });



    AIObject* testAI = new AIObject(nodeGraph);
    testAI->AIAgent->target = player;
    testAI->physics->SetPosition({ 1000, 500 });
    
    

    while (!WindowShouldClose()) {
        DeltaTime = timer.RecordNewTime();

        if (IsKeyPressed(KEY_SPACE)) {
            testAI->AIAgent->m_pathAgent->GoToNode(nodeGraph->GetNode(rand() % ((screenWidth / cellSize)-1) + 1, rand() % ((screenHeight / cellSize)-1) + 1));
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

    PhysicsComponent::GlobalCollisionCheck(DeltaTime);
}


void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(0, 0);
    
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->Draw();
    }
    //nodeGraph->Draw();
    EndDrawing();
}