#include "Behaviour.h"
#include "Agent.h"

void Behaviours::WanderBehaviour::Enter(Agent* agent)
{
}

// WANDER BEHAVIOUR
void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->m_pathAgent->GetPath().empty()) {

		cooldownCount += deltaTime;

		if (cooldownCount >= cooldown) {
			agent->m_pathAgent->GoToNode(agent->m_pathAgent->parentGraph->GetRandomNode());

			cooldown = rand() % 3 + 1;
			cooldownCount = 0;
		}

	}
}
void Behaviours::WanderBehaviour::Exit(Agent* agent)
{
}
//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// GO TO POINT BEHAVIOUR
void GoToPointBehaviour::Update(Agent* agent, float deltaTime)
{
	// read mouseclicks, left for start node, end for right node
	if (IsMouseButtonPressed(0))
	{
		Vector2 mousePos = GetMousePosition();

		agent->m_pathAgent->GoTo({ mousePos.x, mousePos.y });
	}
}

//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// FOLOW TARGET BEHAVIOUR
void FollowTargetBehaviour::Update(Agent* agent, float deltaTime)
{
	cooldownCount += deltaTime;
	if (cooldownCount < cooldown) {
		return;
	}
	cooldownCount = 0;

	// check if the agent has moved significantly from its last position
	// if so we want to repath towards it
	Object* target = agent->target;

	Vector2 diff = target->physics->GetPosition(), lastTargetPosition;
	float dist = Vector2DotProduct(diff, diff);
	float cellSize = agent->m_pathAgent->parentGraph->m_cellSize;
	if (dist > (cellSize * cellSize))
	{
		lastTargetPosition = target->physics->GetPosition();
		agent->m_pathAgent->GoTo(lastTargetPosition);
	}

}
void FollowTargetBehaviour::Exit(Agent* agent)
{
}
void FollowTargetBehaviour::Enter(Agent* agent)
{
	// red when following
	agent->SetColour({ 255,0,0,255 });
	agent->m_pathAgent->ResetPath();
}
//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// SELECTOR BEHAVIOUR

void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
	Vector2 diff = Vector2Subtract(agent->target->physics->GetPosition(), agent->m_pathAgent->ownerPhysics->GetPosition());
	float dist = Vector2DotProduct(diff, diff);
	float range = agent->m_pathAgent->parentGraph->m_cellSize * 5;

	if (dist < (range * range))
	{
		SetBehaviour(m_b1, agent);
		agent->SetColour({ 255, 0, 0, 255 }); //red
	}
	else
	{
		SetBehaviour(m_b2, agent);
		agent->SetColour({ 0, 255, 255, 255 }); // cyan
	}
	m_selected->Update(agent, deltaTime);
}
void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
{
	if (m_selected != b)
	{
		m_selected = b;
		agent->m_pathAgent->ResetPath();
	}
}


//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// LINGER BEHAVIOUR
void Behaviours::LingerBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->m_pathAgent->hasFinishedPath) {
		cooldownCount += deltaTime;
		if (cooldownCount >= cooldown) {
			Node* gotonode = nullptr;

			for(int i = 0; gotonode == nullptr && i < 100; i++)
			{
				float randomDist = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / radius));

				// Create random direction from -1 to 1 for x and y
				Vector2 randDir = { ((rand() % 2000 - 1000) / 1000.0f) * randomDist,((rand() % 2000 - 1000) / 1000.0f) * randomDist };
				Vector2 location = Vector2Add(agent->m_pathAgent->ownerPhysics->GetPosition(), randDir);

				gotonode = agent->m_pathAgent->parentGraph->GetClosestNode(location);
			}
			
			agent->m_pathAgent->GoToNode(gotonode);


			cooldownCount = 0;
			cooldown = rand() % 3 + 1;
			gotonode = nullptr;

		}
	}



}
