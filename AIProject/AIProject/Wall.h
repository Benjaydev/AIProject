#pragma once
#include "Obstacle.h"
class Wall : public Obstacle
{
public:
	Wall(float x, float y, int width, int height, int scale, float rotation, char* textureFileName, int colour = 0x4E3524FF);
	virtual ~Wall();


	void Update(float DeltaTime) override;
};

