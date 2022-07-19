#include "Wall.h"

Wall::Wall(float x, float y, int width, int height, char* textureFileName)
{
    // Load image that is one pixel big
    LoadSprite(textureFileName);
    // Expand by width and height
    sprite->texture->width = width;
    sprite->texture->height = height;

    InitiateObstacle(x, y);

}

Wall::~Wall()
{
}

void Wall::Update(float DeltaTime)
{
    Obstacle::Update(DeltaTime);


}
