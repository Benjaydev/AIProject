#include "Condition.h"
#include "AIObject.h"
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
		viewTimeCount = fmaxf(0, viewTimeCount - deltaTime);
		return false;
	}

	
}

bool Conditions::SeeSuspiciousCondition::IsTrue(Agent* agent, float deltaTime)
{

	Vector2 coneDir = agent->pathAgent->ownerPhysics->GetFacingDirection();
	Vector2 dirToPoint = Vector2Subtract(agent->target->physics->GetPosition(), agent->pathAgent->ownerPhysics->GetPosition());
	float angle = acos(Vector2DotProduct(Vector2Normalize(dirToPoint), coneDir));


	// Check if any surrounding AI is fleeing
	for (int i = 0; i < AIObject::WorldAIInstances.size(); i++) {
		if (AIObject::WorldAIInstances[i]->AIAgent == agent) {
			continue;
		}
		// Get distance from other agent
		Vector2 diff = Vector2Subtract(agent->pathAgent->ownerPhysics->GetPosition(), AIObject::WorldAIInstances[i]->AIAgent->pathAgent->ownerPhysics->GetPosition());
		float dist = Vector2DotProduct(diff, diff);
		if (dist <= (viewDistance * viewDistance)) {
			// If other agent is fleeing or chasing target
			if (AIObject::WorldAIInstances[i]->AIAgent->currentBehaviour->name == "Flee" || AIObject::WorldAIInstances[i]->AIAgent->currentBehaviour->name == "Follow") {
				viewTimeCount += deltaTime;
			}
		}
	}


	if (angle * RAD2DEG <= viewAngle && Vector2Length(dirToPoint) <= viewDistance) {		
		// Check if target has suspicious weapon
		if (((GameObject*)agent->target)->hasSuspiciousWeapon()) {
			viewTimeCount += deltaTime;
		}
	}
	else {
		viewTimeCount = fmaxf(0, viewTimeCount - deltaTime);
	}


	// If suspicious timer has run out, the agent is now suspicious forever
	if (viewTimeCount >= viewTime) {
		viewTimeCount = viewTime;
		isSuspicious = true;
		return true;
	}
	return false;
}
