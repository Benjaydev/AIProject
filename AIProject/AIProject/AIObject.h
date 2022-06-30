#pragma once
#include "Pathfinding.h"
#include "Object.h"
using namespace Pathfinding;

class AIObject : public Object
{
public:
	AIObject();
	virtual ~AIObject();

	PathAgent* AIAgent;

	void Update(float DeltaTime) override;
	void Draw() override;

};

