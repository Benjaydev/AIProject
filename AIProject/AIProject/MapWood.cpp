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
    new Wall(4, 0, 13, 1, 10, 90, (char*)"Images/WallTile.png");
    new Wall(21, 0, 24, 1, 10, 90, (char*)"Images/WallTile.png");
    
    // Bottom
    new Wall(4, 30, 18, 1, 10, 90, (char*)"Images/WallTile.png");
    new Wall(26, 30, 19, 1, 10, 90, (char*)"Images/WallTile.png");
    
    // Right
    new Wall(45, 1, 1, 19, 10, 0, (char*)"Images/WallTile.png");
    new Wall(45, 24, 1, 6, 10, 0, (char*)"Images/WallTile.png");


    // INSIDE HOUSE
    // Top Rooms
        // Left most room wall
    new Wall(5, 1, 1, 4, 10, 0, (char*)"Images/WallTile.png");
    new Wall(5, 9, 1, 5, 10, 0, (char*)"Images/WallTile.png");

        // Toilet wall
    new Wall(6, 9, 1, 1, 10, 90, (char*)"Images/WallTile.png");

        // Second left most room wall
    new Wall(11, 5, 1, 9, 10, 0, (char*)"Images/WallTile.png");

        // Second right most room wall
    new Wall(30, 1, 1, 5, 10, 0, (char*)"Images/WallTile.png");
    new Wall(30, 9, 1, 5, 10, 0, (char*)"Images/WallTile.png");
    
        // Right most room wall
    new Wall(41, 1, 1, 4, 10, 0, (char*)"Images/WallTile.png");
    new Wall(41, 9, 1, 5, 10, 0, (char*)"Images/WallTile.png");

    
        // Room bottom wall
    new Wall(6, 14, 29, 1, 10, 90, (char*)"Images/WallTile.png");
    new Wall(39, 14, 6, 1, 10, 90, (char*)"Images/WallTile.png");



    // Bottom Rooms
        // Top walls
    new Wall(1, 20, 4, 1, 10, 90, (char*)"Images/WallTile.png");
    new Wall(9, 20, 9, 1, 10, 90, (char*)"Images/WallTile.png");
    new Wall(22, 20, 4, 1, 10, 90, (char*)"Images/WallTile.png");

        // Middle wall
    new Wall(13, 21, 1, 9, 10, 0, (char*)"Images/WallTile.png");
        // Right wall
    new Wall(26, 21, 1, 9, 10, 0, (char*)"Images/WallTile.png");





    // wall connectors

    // Dead ends

    // Main walls
        // Top wall
    new Wall(3, 0, 1, 1, 10, 90, (char*)"Images/WallTileSingle.png");
    new Wall(17, 0, 1, 1, 10, -90, (char*)"Images/WallTileSingle.png");
    new Wall(20, 0, 1, 1, 10, 90, (char*)"Images/WallTileSingle.png");

        // Left
    new Wall(0, 0, 1, 1, 10, 180, (char*)"Images/WallTileSingle.png");
    new Wall(0, 30, 1, 1, 10, 0, (char*)"Images/WallTileSingle.png");


        // Right
    new Wall(45, 20, 1, 1, 10, 0, (char*)"Images/WallTileSingle.png");
    new Wall(45, 23, 1, 1, 10, 180, (char*)"Images/WallTileSingle.png");
            // Corners

    new Wall(45, 0, 1, 1, 10, 0, (char*)"Images/WallTileSingle.png");
    new Wall(45, 30, 1, 1, 10, 0, (char*)"Images/WallTileSingle.png");


        // Bottom
    new Wall(3, 30, 1, 1, 10, 90, (char*)"Images/WallTileSingle.png");
    new Wall(22, 30, 1, 1, 10, -90, (char*)"Images/WallTileSingle.png");
    new Wall(25, 30, 1, 1, 10, 90, (char*)"Images/WallTileSingle.png");






    // Top
        // Left most room walls
    new Wall(5, 5, 1, 1, 10, 0, (char*)"Images/WallTileSingle.png");
    new Wall(5, 8, 1, 1, 10, 180, (char*)"Images/WallTileSingle.png");
    
        // Toilet ends
    new Wall(7, 9, 1, 1, 10, -90, (char*)"Images/WallTileSingle.png");
    new Wall(10, 9, 1, 1, 10, 90, (char*)"Images/WallTileSingle.png");

        // Second left most room wall
    new Wall(11, 4, 1, 1, 10, 180, (char*)"Images/WallTileSingle.png");


        // Second right most room walls
    new Wall(30, 5, 1, 1, 10, 0, (char*)"Images/WallTileSingle.png");
    new Wall(30, 8, 1, 1, 10, 180, (char*)"Images/WallTileSingle.png");
    
        // Right most room walls
    new Wall(41, 5, 1, 1, 10, 0, (char*)"Images/WallTileSingle.png");
    new Wall(41, 8, 1, 1, 10, 180, (char*)"Images/WallTileSingle.png");

        // Room bottom wall
    new Wall(5, 14, 1, 1, 10, 90, (char*)"Images/WallTileSingle.png");

    new Wall(35, 14, 1, 1, 10, -90, (char*)"Images/WallTileSingle.png");
    new Wall(38, 14, 1, 1, 10, 90, (char*)"Images/WallTileSingle.png");


    // Bottom rooms
        // Top most wall
    new Wall(5, 20, 1, 1, 10, -90, (char*)"Images/WallTileSingle.png");
    new Wall(8, 20, 1, 1, 10, 90, (char*)"Images/WallTileSingle.png");
    
    new Wall(18, 20, 1, 1, 10, -90, (char*)"Images/WallTileSingle.png");
    new Wall(21, 20, 1, 1, 10, 90, (char*)"Images/WallTileSingle.png");

        //Right most wall
    new Wall(26, 20, 1, 1, 10, 180, (char*)"Images/WallTileSingle.png");





    // Garden walls
    // Entrance fences
    new Wall(0, -17, 1, 17, 10, 0, (char*)"Images/FenceTile.png", 0x888888FF);
    new Wall(3, -17, 1, 17, 10, 0, (char*)"Images/FenceTile.png", 0x888888FF);

    // Bush
    // Top left
    new Wall(3, -17, 43, 1, 10, 90, (char*)"Images/BushTile.png", 0x888888FF);

    // Centre corner piece
    // Fences
    new Wall(45, -5, 1, 5, 10, 0, (char*)"Images/FenceTile.png", 0x888888FF);
    new Wall(46, 0, 5, 1, 10, 90, (char*)"Images/FenceTile.png", 0x888888FF);

    // Bush
    new Wall(45, -16, 1, 5, 10, 90, (char*)"Images/BushTile.png", 0x888888FF);
    new Wall(46, -12, 12, 1, 10, 90, (char*)"Images/BushTile.png", 0x888888FF);
    new Wall(57, -11, 1, 11, 10, 90, (char*)"Images/BushTile.png", 0x888888FF);
    new Wall(57, 0, 19, 1, 10, 90, (char*)"Images/BushTile.png", 0x888888FF);

    // Right
    //Bush
    new Wall(75, 1, 1, 30, 10, 90, (char*)"Images/BushTile.png", 0x888888FF);
    new Wall(46, 30, 29, 1, 10, 90, (char*)"Images/BushTile.png", 0x888888FF);


    // Bottom fences
    new Wall(0, 31, 1, 4, 10, 0, (char*)"Images/FenceTile.png", 0x888888FF);
    new Wall(25, 31, 1, 4, 10, 0, (char*)"Images/FenceTile.png", 0x888888FF);

    new Wall(0, 35, 26, 1, 10, 90, (char*)"Images/FenceTile.png", 0x888888FF);

    // Out of bounds
    // Invisible walls to block navigation outside of the map
    new Wall(46, -15, 29, 3, 10, 0, (char*)"Images/WallTile.png", 0x00000000, false);
    new Wall(58, -12, 17, 12, 10, 0, (char*)"Images/WallTile.png", 0x00000000, false);
    new Wall(26, 31, 50, 4, 10, 0, (char*)"Images/WallTile.png", 0x00000000, false);






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
