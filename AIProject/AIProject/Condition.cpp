#include "Condition.h"
using namespace Conditions;

bool SqrDistanceCondition::IsTrue(Agent* agent)
{
	Vector2 diff = Vector2Subtract(agent->target->physics->GetPosition(), agent->m_pathAgent->ownerPhysics->GetPosition());
	float dist = Vector2DotProduct(diff, diff);
	return (dist < (m_distance* m_distance)) == m_lessThan;
}