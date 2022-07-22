#include "Game.h"
#include "Timer.h"
#include "AICivilian.h"
#include "AISecurityGuard.h"
#include "Behaviour.h"
using namespace Behaviours;


std::vector<Object*> Game::objects = std::vector<Object*>();
std::vector<Vector2> Game::importantLocations = std::vector<Vector2>();
int Game::lifetimeObjectCount = 0;;
bool Game::DebugActive = false;
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

    InitWindow(screenWidth, screenHeight, "AI Project");

    map1 = new MapWood();
    currentMap = (Map*)map1;


    nodeGraph = new NodeGraph();
    int cellSize = 25;
    nodeGraph->GenerateGrid({ (float)screenWidth*2.5f, (float)screenHeight*2.5f }, cellSize, "Obstacle", 2.0f, {0, -600.0f});

    Timer timer;


    player = new Player();
    player->physics->SetPosition({ 150, 150 });

    
    importantLocations.push_back({851, 275});
    importantLocations.push_back({441, -334});
    importantLocations.push_back({1392, -332});
    importantLocations.push_back({2151, -323});
    importantLocations.push_back({2452, 344});
    importantLocations.push_back({2434, 925});
    importantLocations.push_back({1444, 886});
    

    while (!WindowShouldClose()) {
        DeltaTime = timer.RecordNewTime();

        if (IsKeyPressed(KEY_SPACE)) {
            AIObject* testAI = new AIObject(nodeGraph);
            testAI->AIAgent->target = player;
            testAI->physics->SetPosition({ 0, -600 });
            //testAI->AIAgent->m_pathAgent->GoToNode(nodeGraph->GetNode(rand() % ((screenWidth / cellSize) - 1) + 1, rand() % ((screenHeight / cellSize) - 1) + 1));
            
            
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), player->camera);
            std::cout << mousePos.x << ", " << mousePos.y << std::endl;
            player->physics->SetPosition(mousePos);
        }
        
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), player->camera);
            /*Wall* wall = new Wall(mousePos.x, mousePos.y, 100, 100, 1, 0, (char*)"Images/WhitePixel.png");*/

            AISecurityGuard* testAI = new AISecurityGuard(nodeGraph);
            testAI->AIAgent->target = player;
            testAI->physics->SetPosition(mousePos);
        }

        if (IsKeyPressed(KEY_J)) {
            DebugActive = !DebugActive;
        }
        if (IsKeyPressed(KEY_G)) {
            nodeGraph->GenerateGrid({ (float)screenWidth * 2.5f, (float)screenHeight * 2.5f }, cellSize, "Obstacle", 1.75f, { 0, -600.0f });
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
    Vector2 min = GetScreenToWorld2D({ 0,0 }, player->camera);
    Vector2 max = GetScreenToWorld2D({ (float)GetScreenWidth(),(float)GetScreenHeight()}, player->camera);
    WorldBorders.x = min.x;
    WorldBorders.y = min.y;
    WorldBorders.z = max.x;
    WorldBorders.w = max.y;


    for (int i = 0; i < objects.size(); i++) {

        objects[i]->Update(DeltaTime);
    }
    
    PhysicsComponent::GlobalCollisionCheck(DeltaTime);

}


void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(player->camera);
    currentMap->DrawBackground();


    Vector2 pos = GetScreenToWorld2D({0, 0}, player->camera);
    DrawFPS(pos.x, pos.y);

    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->isOnScreen) {
            objects[i]->Draw();
        }
    }

    if (DebugActive) {
        nodeGraph->Draw();
    }
    
    EndMode2D();
    EndDrawing();
}