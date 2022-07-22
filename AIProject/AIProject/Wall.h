#pragma once
#include "Obstacle.h"
class Wall : public Obstacle
{
public:
	Wall(float x, float y, int width, int height, int scale, float rotation, Texture2D textureFileName, int colour = 0xFFFFFFFF, bool shouldTile = true);
	virtual ~Wall();


	void Update(float DeltaTime) override;
};

