#include "MapWood.h"

MapWood::MapWood()
{
    floorBackground = LoadTexture((char*)"Images/Floor.png");
    grassBackground = LoadTexture((char*)"Images/Grass.png");
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
            if (i == 0 || j == 0 || i == 4 || j == 4) {
                DrawTexture(grassBackground, j * 1200 + BackgroundStartOffset.x, i * 800 + BackgroundStartOffset.y, WHITE);
                continue;
            }
            DrawTexture(floorBackground, j * 1200 + BackgroundStartOffset.x, i * 800 + BackgroundStartOffset.y, WHITE);
        }
    }

}
