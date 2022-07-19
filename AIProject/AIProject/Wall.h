#pragma once
#include "Obstacle.h"
class Wall : public Obstacle
{
public:
	Wall(float x, float y, int width, int height, char* textureFileName);
	virtual ~Wall();


	void Update(float DeltaTime) override;
};

