#include "MapWood.h"
#include "Wall.h"
#include "DecorObstacle.h"

MapWood::MapWood()
{
    floorBackground = LoadTexture((char*)"Images/Floor.png");
    grassBackground = LoadTexture((char*)"Images/Grass.png");


    // Obstacles
    Image* toiletImg0 = new Image(LoadImage((char*)"Images/Toilet.png"));
    Image* toiletImgN180 = new Image(LoadImage((char*)"Images/Toilet.png")); 
    ImageRotateCCW(toiletImgN180);
    ImageRotateCCW(toiletImgN180);
    Texture2D toilet0 = LoadTextureFromImage(*toiletImg0);
    Texture2D toiletN180 = LoadTextureFromImage(*toiletImgN180);
    new DecorObstacle(360, 510, 1, 0, toilet0);
    new DecorObstacle(1720, 40, 1, 0, toiletN180);

    Image* SinkImgN90 = new Image(LoadImage((char*)"Images/Sink.png"));
    ImageRotateCCW(SinkImgN90);
    Texture2D toiletSinkN90 = LoadTextureFromImage(*SinkImgN90);
    new DecorObstacle(235, 440, 1, 0, toiletSinkN90);
    new DecorObstacle(1670, 120, 1, 0, toiletSinkN90);
    
    Texture2D bathtub0 = LoadTexture((char*)"Images/Bathtub.png");
    new DecorObstacle(1750, 450, 1, 0, bathtub0);


    Image* bedImg0 = new Image(LoadImage((char*)"Images/Bed.png"));
    Image* bedImg180 = new Image(LoadImage((char*)"Images/Bed.png"));
    ImageRotateCW(bedImg180);
    ImageRotateCW(bedImg180);
    Texture2D bed0 = LoadTextureFromImage(*bedImg0);
    Texture2D bed180 = LoadTextureFromImage(*bedImg180);
    new DecorObstacle(1400, 40, 1.5, 0, bed0);
    new DecorObstacle(450, 1055, 1.5, 0, bed180);
    new DecorObstacle(720, 1055, 1.5, 0, bed180);

    Texture2D shelf0 = LoadTexture((char*)"Images/Shelf.png");
    new DecorObstacle(560, 850, 1, 0, shelf0);
    new DecorObstacle(470, 850, 1, 0, shelf0);
    new DecorObstacle(470, 950, 1, 0, shelf0);

    new DecorObstacle(1235, 370, 1, 0, shelf0);
    new DecorObstacle(1235, 470, 1, 0, shelf0);
    
    new DecorObstacle(475, 200, 1, 0, shelf0);
    new DecorObstacle(475, 320, 1, 0, shelf0);
    new DecorObstacle(475, 440, 1, 0, shelf0);

    Texture2D drawer0 = LoadTexture((char*)"Images/Drawer.png");
    new DecorObstacle(1345, 40, 1, 0, drawer0);
    new DecorObstacle(1480, 40, 1, 0, drawer0);

    new DecorObstacle(665, 1155, 1, 0, drawer0);
    new DecorObstacle(800, 1155, 1, 0, drawer0);

    new DecorObstacle(395, 1155, 1, 0, drawer0);

    Image* tableImg0 = new Image(LoadImage((char*)"Images/Table.png"));
    Image* tableImg90 = new Image(LoadImage((char*)"Images/Table.png"));
    ImageRotateCW(tableImg90);
    Texture2D table0 = LoadTextureFromImage(*tableImg0);
    Texture2D table90 = LoadTextureFromImage(*tableImg90);
    new DecorObstacle(1580, 450, 1, 0, table90);
    new DecorObstacle(980, 845, 1, 0, table90);
    new DecorObstacle(50, 845, 1, 0, table90);

    new DecorObstacle(690, 450, 2, 0, table0);
    new DecorObstacle(940, 450, 2, 0, table0);


    Texture2D metalTable = LoadTexture((char*)"Images/MetalTable.png");
    new DecorObstacle(1180, 1155, 1, 0, metalTable);
    new DecorObstacle(1280, 1155, 1, 0, metalTable);
    new DecorObstacle(1380, 1155, 1, 0, metalTable);

    
    new DecorObstacle(1180, 1005, 1, 0, metalTable);
    new DecorObstacle(1280, 1005, 1, 0, metalTable);
    new DecorObstacle(1380, 1005, 1, 0, metalTable);

    Texture2D stove = LoadTexture((char*)"Images/Stove.png");
    new DecorObstacle(1480, 1155, 1, 0, stove);
    new DecorObstacle(1530, 1155, 1, 0, stove);

    Texture2D fridge = LoadTexture((char*)"Images/Fridge.png");
    new DecorObstacle(1080, 1155, 1, 0, fridge);
    new DecorObstacle(1130, 1155, 1, 0, fridge);

    Texture2D metalSink = LoadTexture((char*)"Images/MetalSink.png");
    new DecorObstacle(1580, 1155, 1, 0, metalSink);
    new DecorObstacle(1630, 1155, 1, 0, metalSink);

    // House width = 45 tiles
    // House height = 30 tiles
    
    
    Texture2D wallTile = LoadTexture((char*)"Images/WallTile.png");
    Texture2D wallTileSingle = LoadTexture((char*)"Images/WallTileSingle.png");
    Texture2D fenceTile = LoadTexture((char*)"Images/FenceTile.png");
    Texture2D bushTile = LoadTexture((char*)"Images/BushTile.png");
  


    // Outer house walls
    // Left
    new Wall(0, 1, 1, 29, 10, 0, wallTile);

    // Top
    new Wall(4, 0, 13, 1, 10, 90, wallTile);
    new Wall(21, 0, 24, 1, 10, 90, wallTile);

    // Bottom
    new Wall(4, 30, 18, 1, 10, 90, wallTile);
    new Wall(26, 30, 19, 1, 10, 90, wallTile);

    // Right
    new Wall(45, 1, 1, 19, 10, 0, wallTile);
    new Wall(45, 24, 1, 6, 10, 0, wallTile);


    // INSIDE HOUSE
    // Top Rooms
        // Left most room wall
    new Wall(5, 1, 1, 4, 10, 0, wallTile);
    new Wall(5, 9, 1, 5, 10, 0, wallTile);

    // Toilet wall
    new Wall(6, 9, 1, 1, 10, 90, wallTile);

    // Second left most room wall
    new Wall(11, 5, 1, 9, 10, 0, wallTile);

    // Second right most room wall
    new Wall(30, 1, 1, 5, 10, 0, wallTile);
    new Wall(30, 9, 1, 5, 10, 0, wallTile);

    // Right most room wall
    new Wall(41, 1, 1, 4, 10, 0, wallTile);
    new Wall(41, 9, 1, 5, 10, 0, wallTile);


    // Room bottom wall
    new Wall(6, 14, 29, 1, 10, 90, wallTile);
    new Wall(39, 14, 6, 1, 10, 90, wallTile);



    // Bottom Rooms
        // Top walls
    new Wall(1, 20, 4, 1, 10, 90, wallTile);
    new Wall(9, 20, 9, 1, 10, 90, wallTile);
    new Wall(22, 20, 4, 1, 10, 90, wallTile);

    // Middle wall
    new Wall(13, 21, 1, 9, 10, 0, wallTile);
    // Right wall
    new Wall(26, 21, 1, 9, 10, 0, wallTile);



    // wall connectors

    // Dead ends

    // Main walls
        // Top wall
    new Wall(3, 0, 1, 1, 10, 90, wallTileSingle);
    new Wall(17, 0, 1, 1, 10, -90, wallTileSingle);
    new Wall(20, 0, 1, 1, 10, 90, wallTileSingle);

    // Left
    new Wall(0, 0, 1, 1, 10, 180, wallTileSingle);
    new Wall(0, 30, 1, 1, 10, 0, wallTileSingle);


    // Right
    new Wall(45, 20, 1, 1, 10, 0, wallTileSingle);
    new Wall(45, 23, 1, 1, 10, 180, wallTileSingle);
    // Corners

    new Wall(45, 0, 1, 1, 10, 0, wallTileSingle);
    new Wall(45, 30, 1, 1, 10, 0, wallTileSingle);


    // Bottom
    new Wall(3, 30, 1, 1, 10, 90, wallTileSingle);
    new Wall(22, 30, 1, 1, 10, -90, wallTileSingle);
    new Wall(25, 30, 1, 1, 10, 90, wallTileSingle);



    // Top
        // Left most room walls
    new Wall(5, 5, 1, 1, 10, 0, wallTileSingle);
    new Wall(5, 8, 1, 1, 10, 180, wallTileSingle);

    // Toilet ends
    new Wall(7, 9, 1, 1, 10, -90, wallTileSingle);
    new Wall(10, 9, 1, 1, 10, 90, wallTileSingle);

    // Second left most room wall
    new Wall(11, 4, 1, 1, 10, 180, wallTileSingle);


    // Second right most room walls
    new Wall(30, 5, 1, 1, 10, 0, wallTileSingle);
    new Wall(30, 8, 1, 1, 10, 180, wallTileSingle);

    // Right most room walls
    new Wall(41, 5, 1, 1, 10, 0, wallTileSingle);
    new Wall(41, 8, 1, 1, 10, 180, wallTileSingle);

    // Room bottom wall
    new Wall(5, 14, 1, 1, 10, 90, wallTileSingle);

    new Wall(35, 14, 1, 1, 10, -90, wallTileSingle);
    new Wall(38, 14, 1, 1, 10, 90, wallTileSingle);


    // Bottom rooms
        // Top most wall
    new Wall(5, 20, 1, 1, 10, -90, wallTileSingle);
    new Wall(8, 20, 1, 1, 10, 90, wallTileSingle);

    new Wall(18, 20, 1, 1, 10, -90, wallTileSingle);
    new Wall(21, 20, 1, 1, 10, 90, wallTileSingle);

    //Right most wall
    new Wall(26, 20, 1, 1, 10, 180, wallTileSingle);



    // Garden walls
    // Entrance fences
    new Wall(0, -17, 1, 17, 10, 45, fenceTile, 0x888888FF);
    new Wall(3, -17, 1, 17, 10, 45, fenceTile, 0x888888FF);

    // Bush
    // Top left
    new Wall(3, -17, 43, 1, 10, 45, bushTile, 0x888888FF);

    // Centre corner piece
    // Fences
    new Wall(45, -5, 1, 5, 10, 45, fenceTile, 0x888888FF);
    new Wall(46, 0, 5, 1, 10, 45, fenceTile, 0x888888FF);

    // Bush
    new Wall(45, -16, 1, 5, 10, 45, bushTile, 0x888888FF);
    new Wall(46, -12, 12, 1, 10, 45, bushTile, 0x888888FF);
    new Wall(57, -11, 1, 11, 10, 45, bushTile, 0x888888FF);
    new Wall(57, 0, 19, 1, 10, 45, bushTile, 0x888888FF);

    // Right
    //Bush
    new Wall(75, 1, 1, 30, 10, 45, bushTile, 0x888888FF);
    new Wall(46, 30, 29, 1, 10, 45, bushTile, 0x888888FF);


    // Bottom fences
    new Wall(0, 31, 1, 4, 10, 45, fenceTile, 0x888888FF);
    new Wall(25, 31, 1, 4, 10, 45, fenceTile, 0x888888FF);

    new Wall(0, 35, 26, 1, 10, 45, fenceTile, 0x888888FF);

    // Out of bounds
    // Invisible walls to block navigation outside of the map
    new Wall(46, -15, 29, 3, 10, 0, wallTile, 0x00000000, false);
    new Wall(58, -12, 17, 12, 10, 0, wallTile, 0x00000000, false);
    new Wall(26, 31, 50, 4, 10, 0, wallTile, 0x00000000, false);


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


    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i == 0 || i == 1) {
                DrawTexture(grassBackground, j * 1200 + BackgroundStartOffset.x, i * 800 + BackgroundStartOffset.y, WHITE);
            }
            else if (j == 0 || j == 1) {
                DrawTexture(grassBackground, j * 1200 + BackgroundStartOffset.x - 200, i * 800 + BackgroundStartOffset.y, WHITE);
            }
            else if (i == 4 || i == 5) {
                DrawTexture(grassBackground, j * 1200 + BackgroundStartOffset.x -400, i * 800 + BackgroundStartOffset.y-360, WHITE);
            }
            else if (j == 4 || j == 5) {
                DrawTexture(grassBackground, j * 1200 + BackgroundStartOffset.x - 960, i * 800 + BackgroundStartOffset.y, WHITE);
            }
            else {
                DrawTexture(floorBackground, j * 1000 + BackgroundStartOffset.x, i * 800 + BackgroundStartOffset.y, WHITE);
            }
        }
    }


   /*for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 80; j++) {
            DrawText(std::to_string(j * 40).c_str(), (j * 40) + 5, i * 40, 16, BLACK);
            DrawText(std::to_string(i * 40).c_str(), (j * 40) + 5, (i * 40) + 20, 16, BLACK);

            DrawRectangleLines(j * 40, i * 40, 40, 40, RED);
        }
    }*/


}
