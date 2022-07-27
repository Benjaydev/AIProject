#pragma once
#include "Obstacle.h"
class DecorObstacle : public Obstacle
{
public:
	DecorObstacle(int x, int y, float scale, float rotation, Texture2D texture, int colour = 0xFFFFFFFF);
	virtual ~DecorObstacle();

	void Update(float DeltaTime) override;
};

