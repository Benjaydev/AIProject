#include "Wall.h"

Wall::Wall(float x, float y, int tileWidth, int tileHeight, int scale, float rotation, char* textureFileName, int colour)
{
    // Load image that is one pixel big
    LoadSprite(textureFileName);
    // Expand by width and height
    //sprite->texture->width = width;
    //sprite->texture->height = height;
    sprite->tiling = { (float)tileWidth, (float)tileHeight };
    sprite->SetScale(scale);
    sprite->tiledSpriteRotation = rotation;

    sprite->colour = GetColor(colour);

    InitiateObstacle(x* sprite->texture->width, y* sprite->texture->height);

}

Wall::~Wall()
{
}

void Wall::Update(float DeltaTime)
{
    Obstacle::Update(DeltaTime);


}
