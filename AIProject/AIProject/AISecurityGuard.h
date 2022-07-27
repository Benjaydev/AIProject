#pragma once
#include "AIObject.h"
class AISecurityGuard : public AIObject
{
public:
	AISecurityGuard(NodeGraph* graph);

	float shootCooldown = 1;
	float shootCooldownCount = 0;
	void Update(float DeltaTime) override;
};

