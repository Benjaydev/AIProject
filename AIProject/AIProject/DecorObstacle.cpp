#include "DecorObstacle.h"

DecorObstacle::DecorObstacle(int x, int y, float scale, float rotation, Texture2D texture, int colour)
{
	// Load image that is one pixel big
	CreateSpriteFromTexture(texture);

	sprite->tiling = { 1, 1 };
	sprite->Scale(scale);
	sprite->tiledSpriteRotation = rotation;
	sprite->shouldTile = false;

	sprite->colour = GetColor(colour);
	InitiateObstacle(x, y);
}

DecorObstacle::~DecorObstacle()
{
}

void DecorObstacle::Update(float DeltaTime)
{
	Obstacle::Update(DeltaTime);
}
