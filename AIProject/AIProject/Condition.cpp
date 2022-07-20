#include "Condition.h"
using namespace Conditions;

bool SqrDistanceCondition::IsTrue(Agent* agent, float deltaTime)
{
	Vector2 diff = Vector2Subtract(agent->target->physics->GetPosition(), agent->pathAgent->ownerPhysics->GetPosition());
	float dist = Vector2DotProduct(diff, diff);
	return ((dist < (m_distance* m_distance)) == m_lessThan);
}

bool Conditions::SeeCondition::IsTrue(Agent* agent, float deltaTime)
{
	Vector2 coneDir = agent->pathAgent->ownerPhysics->GetFacingDirection();
	Vector2 dirToPoint = Vector2Subtract(agent->target->physics->GetPosition(), agent->pathAgent->ownerPhysics->GetPosition());
	float angle = acos(Vector2DotProduct(Vector2Normalize(dirToPoint), coneDir));

	if (angle*RAD2DEG <= viewAngle && Vector2Length(dirToPoint) <= viewDistance) {
		viewTimeCount += deltaTime;
		return viewTimeCount >= viewTime;
	}
	else {
		agent->target->hasSprite = true;
		viewTimeCount = fmaxf(0, viewTimeCount - deltaTime);
		return false;
	}

	
}
