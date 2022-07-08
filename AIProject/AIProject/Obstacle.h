#pragma once
#include "Object.h"
class Obstacle : public Object
{
public:
	Obstacle();
	virtual ~Obstacle();


	virtual void InitiateObstacle(float x, float y);


	void Update(float DeltaTime) override;
};

