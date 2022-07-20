#include "Game.h"
#include "Timer.h"
#include "AIObject.h"
#include "Behaviour.h"
using namespace Behaviours;


std::vector<Object*> Game::objects = std::vector<Object*>();
int Game::lifetimeObjectCount = 0;;
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

    InitWindow(screenWidth, screenHeight, "AI Project");


    map1 = new MapWood();
    currentMap = (Map*)map1;


    nodeGraph = new NodeGraph();
    int cellSize = 25;
    nodeGraph->GenerateGrid({ (float)screenWidth*2.5f, (float)screenHeight*2.5f }, cellSize, "Obstacle", 2, {0, -600.0f});

    Timer timer;


    player = new Player();
    player->physics->SetPosition({ 150, 150 });

    
    

    while (!WindowShouldClose()) {
        DeltaTime = timer.RecordNewTime();

        if (IsKeyPressed(KEY_SPACE)) {
            AIObject* testAI = new AIObject(nodeGraph);
            testAI->AIAgent->target = player;
            testAI->physics->SetPosition({ 1000, 500 });
            //testAI->AIAgent->m_pathAgent->GoToNode(nodeGraph->GetNode(rand() % ((screenWidth / cellSize) - 1) + 1, rand() % ((screenHeight / cellSize) - 1) + 1));
            
            
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), player->camera);
            //Wall* wall = new Wall(mousePos.x, mousePos.y, 100, 900, 1, 0, (char*)"Images/WhitePixel.png");

            player->physics->SetPosition(mousePos);

            
        }
        if (IsKeyPressed(KEY_G)) {
            nodeGraph->GenerateGrid({ (float)screenWidth * 3, (float)screenHeight * 3 }, cellSize, "Obstacle");
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
    //std::cout << "Update start" << std::endl;
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

    //std::cout << "Update end" << std::endl;
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

    nodeGraph->Draw();
    EndMode2D();
    EndDrawing();
}