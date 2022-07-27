#include "Wall.h"

Wall::Wall(float x, float y, int tileWidth, int tileHeight, int scale, float rotation, Texture2D texture, int colour, bool shouldTile)
{
    // Load image that is one pixel big
    CreateSpriteFromTexture(texture);
    // Expand by width and height

    sprite->tiling = { (float)tileWidth, (float)tileHeight };
    sprite->Scale(scale);
    sprite->tiledSpriteRotation = rotation;
    sprite->shouldTile = shouldTile;

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
