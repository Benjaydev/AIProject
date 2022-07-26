#include "Condition.h"
#include "AIObject.h"
#include "Game.h"

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
	if (agent->target == nullptr) {
		return false;
	}


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
			if (AIObject::WorldAIInstances[i]->AIAgent->currentBehaviour->name == "Flee" 
				|| AIObject::WorldAIInstances[i]->AIAgent->currentBehaviour->name == "Follow"
				|| AIObject::WorldAIInstances[i]->AIAgent->currentBehaviour->name == "Search") {
				return true;
			}
		}
		// If near dead agent
		if (dist <= (viewDistance/4) * (viewDistance/4) && !AIObject::WorldAIInstances[i]->AIAgent->active) {
			return true;
		}
	}


	// Check if AI can see target
	Vector2 coneDir = agent->pathAgent->ownerPhysics->GetFacingDirection();
	Vector2 dirToPoint = Vector2Subtract(agent->target->physics->GetPosition(), agent->pathAgent->ownerPhysics->GetPosition());
	Vector2 normDir = Vector2Normalize(dirToPoint);
	// If distance to target is outside view
	float distance = Vector2Length(dirToPoint);

	float angle = acos(Vector2DotProduct(normDir, coneDir));

	// Create ray collider from agent to target
	RayCollider* ray = new RayCollider(agent->pathAgent->ownerPhysics->GetPosition(), normDir, distance);
	Hit out;

	// Check if view is blocked by obstacle
	for (int i = 0; i < Game::objects.size(); i++) {
		if (Game::objects[i]->tag == agent->pathAgent->parentGraph->obstacleTag) {
			if (ray->Overlaps(Game::objects[i]->physics->collider, out)) {
				delete ray;
				return false;
			}
		}
	}
	delete ray;

	if (angle * RAD2DEG <= viewAngle && distance <= viewDistance) {		
		// Check if target has suspicious weapon or costume is suspicious
		if (((GameObject*)agent->target)->hasSuspiciousWeapon() || ((GameObject*)agent->target)->costume == "") {
			viewTimeCount += deltaTime;
		}
	}
	else {
		viewTimeCount = fmaxf(0, viewTimeCount - deltaTime);
	}


	// If suspicious timer has run out, the agent is now suspicious forever
	if (viewTimeCount >= viewTime) {
		viewTimeCount = viewTime;
		//isSuspicious = true;
		return true;
	}
	return false;
}
