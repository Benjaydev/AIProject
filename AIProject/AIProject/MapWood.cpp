#include "MapWood.h"
#include "Wall.h"

MapWood::MapWood()
{
    floorBackground = LoadTexture((char*)"Images/Floor.png");
    grassBackground = LoadTexture((char*)"Images/Grass.png");


    // House width = 45 tiles
    // House height = 30 tiles
    // Outer house walls
    // Left
    new Wall(0, 1, 1, 29, 10, 0, (char*)"Images/WallTile.png");

    // Top
    new Wall(3, 0, 15, 1, 10, 90, (char*)"Images/WallTile.png");
    new Wall(20, 0, 25, 1, 10, 90, (char*)"Images/WallTile.png");
    
    // Bottom
    new Wall(3, 30, 20, 1, 10, 90, (char*)"Images/WallTile.png");
    new Wall(25, 30, 20, 1, 10, 90, (char*)"Images/WallTile.png");
    
    // Right
    new Wall(45, 1, 1, 20, 10, 0, (char*)"Images/WallTile.png");
    new Wall(45, 23, 1, 7, 10, 0, (char*)"Images/WallTile.png");


    // Garden fences
    new Wall(4, -10, 30, 1, 10, 90, (char*)"Images/FenceTile.png", 0x888888FF);


}

MapWood::~MapWood()
{

}

void MapWood::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
}

void MapWood::DrawBackground()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == 0) {
                DrawTexture(grassBackground, j * 1200 + BackgroundStartOffset.x, i * 800 + BackgroundStartOffset.y, WHITE);
            }
            else if (j == 0) {
                DrawTexture(grassBackground, j * 1200 + BackgroundStartOffset.x - 200, i * 800 + BackgroundStartOffset.y, WHITE);
            }
            else if (i == 3) {
                DrawTexture(grassBackground, j * 1200 + BackgroundStartOffset.x-200, i * 800 + BackgroundStartOffset.y-360, WHITE);
            }
            else if (j == 3) {
                DrawTexture(grassBackground, j * 1200 + BackgroundStartOffset.x - 760, i * 800 + BackgroundStartOffset.y, WHITE);
            }
            else {
                DrawTexture(floorBackground, j * 1000 + BackgroundStartOffset.x, i * 800 + BackgroundStartOffset.y, WHITE);
            }



           
        }
    }

}
