#include "Behaviour.h"
#include "Agent.h"
#include "Game.h"

void Behaviours::WanderBehaviour::Enter(Agent* agent)
{
}

// WANDER BEHAVIOUR
void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->pathAgent->GetPath().empty()) {

		cooldownCount += deltaTime;

		if (cooldownCount >= cooldown) {
			agent->pathAgent->GoToNode(agent->pathAgent->parentGraph->GetRandomNode());

			cooldown = rand() % 3 + 1;
			cooldownCount = 0;
		}

	}
}
void Behaviours::WanderBehaviour::Exit(Agent* agent)
{
}

float WanderBehaviour::Evaluate(Agent* agent)
{
	Object* target = agent->target;
	Vector2 diff = Vector2Subtract(target->physics->GetPosition(), agent->pathAgent->ownerPhysics->GetPosition());
	float sqrDist = Vector2DotProduct(diff, diff);

	// Get value between 0-1
	float cellDist = distanceToExit * agent->pathAgent->parentGraph->m_cellSize;
	float eval = fminf(1, sqrDist / (cellDist * cellDist));

	return eval;
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

		agent->pathAgent->GoTo({ mousePos.x, mousePos.y });
		
	}
}

float Behaviours::GoToPointBehaviour::Evaluate(Agent* agent)
{
	return 0.0f;
}

//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// FOLLOW TARGET BEHAVIOUR
void FollowTargetBehaviour::Update(Agent* agent, float deltaTime)
{
	cooldownCount += deltaTime;
	if (cooldownCount < cooldown && !agent->pathAgent->hasFinishedPath) {
		return;
	}
	cooldownCount = 0;

	// Check if the agent has moved significantly from its last position
	Object* target = agent->target;

	Vector2 diff = Vector2Subtract(target->physics->GetPosition(), lastTargetPosition);
	float dist = Vector2DotProduct(diff, diff);
	float cellSize = agent->pathAgent->parentGraph->m_cellSize;
	if (dist > (cellSize * cellSize))
	{
		lastTargetPosition = target->physics->GetPosition();
		agent->pathAgent->GoTo(lastTargetPosition);
	}

}

void FollowTargetBehaviour::Enter(Agent* agent)
{
	agent->pathAgent->rotateInDesiredDirection = true;
	cooldownCount = cooldown;

	// red when following
	agent->SetColour({ 255,0,0,255 });
	agent->pathAgent->ResetPath();
}

float FollowTargetBehaviour::Evaluate(Agent* agent)
{
	Object* target = agent->target;
	Vector2 diff = Vector2Subtract(target->physics->GetPosition(), agent->pathAgent->ownerPhysics->GetPosition());
	float sqrDist = Vector2DotProduct(diff, diff);

	// Get value between 0-1
	float cellDist = distanceToEnter * agent->pathAgent->parentGraph->m_cellSize;

	return sqrDist < (cellDist* cellDist);
}


//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// FLEE TARGET BEHAVIOUR
void FleeTargetBehaviour::Enter(Agent* agent)
{
	cooldown = rand() % 5 + 3;
	cooldownCount = cooldown;
	agent->pathAgent->rotateInDesiredDirection = true;
}

void FleeTargetBehaviour::Update(Agent* agent, float deltaTime)
{
	cooldownCount += deltaTime;
	if (cooldownCount < cooldown && !agent->pathAgent->hasFinishedPath) {
		return;
	}
	cooldownCount = 0;

	// check if the agent has moved significantly from its last position
	// if so we want to repath towards it
	Object* target = agent->target;

	Vector2 diff = Vector2Subtract(target->physics->GetPosition(), agent->pathAgent->ownerPhysics->GetPosition());
	float dist = Vector2DotProduct(diff, diff);
	float cellSize = agent->pathAgent->parentGraph->m_cellSize;


	Vector2 dir = Vector2Negate(Vector2Normalize(diff));
	Vector2 fleeCheckPoint = Vector2Add(agent->pathAgent->ownerPhysics->GetPosition(), Vector2Scale(dir, 200));

	// Attempt to find location to flee to
	Node* gotonode = nullptr;
	for (int i = 0; gotonode == nullptr && i < 100; i++)
	{
		float randomDist = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50));

		// Create random direction from -1 to 1 for x and y
		Vector2 randDir = { ((rand() % 2000 - 1000) / 1000.0f),((rand() % 2000 - 1000) / 1000.0f) };
		Vector2 location = Vector2Add(fleeCheckPoint, Vector2Scale(randDir, randomDist));

		gotonode = agent->pathAgent->parentGraph->GetClosestNode(location);
	}

	if (gotonode == nullptr) {
		agent->FaceTarget();
	}

	agent->pathAgent->GoToNode(gotonode);
	gotonode = nullptr;
}


float FleeTargetBehaviour::Evaluate(Agent* agent)
{
	Object* target = agent->target;
	Vector2 diff = Vector2Subtract(target->physics->GetPosition(), agent->pathAgent->ownerPhysics->GetPosition());
	float sqrDist = Vector2DotProduct(diff, diff);

	// Get value between 0-1
	float cellDist = distanceToEnter * agent->pathAgent->parentGraph->m_cellSize;

	return sqrDist < (cellDist*cellDist);
}






//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// SELECTOR BEHAVIOUR

void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
	Vector2 diff = Vector2Subtract(agent->target->physics->GetPosition(), agent->pathAgent->ownerPhysics->GetPosition());
	float dist = Vector2DotProduct(diff, diff);
	float range = agent->pathAgent->parentGraph->m_cellSize * 5;

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
		agent->pathAgent->ResetPath();
	}
}


void Behaviours::LingerBehaviour::Enter(Agent* agent)
{
	isFinished = false;
	lifeTime = 10;
}

//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// LINGER BEHAVIOUR
void Behaviours::LingerBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->pathAgent->hasFinishedPath) {
		cooldownCount += deltaTime;
		if (cooldownCount >= cooldown) {
			Node* gotonode = nullptr;

			for(int i = 0; gotonode == nullptr && i < 100; i++)
			{
				float randomDist = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / radius));

				// Create random direction from -1 to 1 for x and y
				Vector2 randDir = { ((rand() % 2000 - 1000) / 1000.0f) * randomDist,((rand() % 2000 - 1000) / 1000.0f) * randomDist };
				Vector2 location = Vector2Add(Vector2Add(agent->pathAgent->ownerPhysics->GetPosition(), Vector2Scale(agent->pathAgent->ownerPhysics->GetFacingDirection(), randomDist*1.1f)), randDir);

				gotonode = agent->pathAgent->parentGraph->GetClosestNode(location);
			}
			
			agent->pathAgent->GoToNode(gotonode);


			cooldownCount = 0;
			cooldown = rand() % 3 + 1;
			gotonode = nullptr;

		}
	}

	lifeTime -= deltaTime;
	if (lifeTime <= 0) {
		isFinished = true;
	}

}

float Behaviours::LingerBehaviour::Evaluate(Agent* agent)
{


	return 0.5f;
}

//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// GO TO IMPORTANT LOCATION BEHAVIOUR
void Behaviours::GoToImportantBehaviour::Enter(Agent* agent)
{
	if (Game::importantLocations.size() > 0) {
		// Get random important location
		Vector2 randLoc = Game::importantLocations[rand() % Game::importantLocations.size()];
		// Displace in random direction
		Vector2 randDir = { ((rand() % 2000 - 1000) / 1000.0f),((rand() % 2000 - 1000) / 1000.0f) };
		float randDist = rand() % 100;
		agent->pathAgent->GoToNode(agent->pathAgent->parentGraph->GetClosestNode( Vector2Add(randLoc,Vector2Scale(randDir, randDist) ) ) );
	}

	isFinished = false;
}

void Behaviours::GoToImportantBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->pathAgent->hasFinishedPath) {
		isFinished = true;
	}
}

float Behaviours::GoToImportantBehaviour::Evaluate(Agent* agent)
{
	return chance;
}


//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// SEARCH AREA BEHAVIOUR
void Behaviours::SearchAreaBehaviour::Enter(Agent* agent)
{
	searchArea = agent->pathAgent->ownerPhysics->GetPosition();
}

void Behaviours::SearchAreaBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->pathAgent->hasFinishedPath) {
		cooldownCount += deltaTime;
		if (cooldownCount >= cooldown) {
			Node* gotonode = nullptr;

			for (int i = 0; gotonode == nullptr && i < 100; i++)
			{
				float randomDist = rand() % (int)radius;

				// Create random direction from -1 to 1 for x and y
				Vector2 randDir = { ((rand() % 2000 - 1000) / 1000.0f),((rand() % 2000 - 1000) / 1000.0f)};
				Vector2 location = Vector2Add(searchArea, Vector2Scale(randDir, randomDist));

				gotonode = agent->pathAgent->parentGraph->GetClosestNode(location);
			}

			agent->pathAgent->GoToNode(gotonode);


			cooldownCount = 0;
			cooldown = rand() % 3 + 1;
			gotonode = nullptr;


			isFinished = true;
		}
	}
}

float Behaviours::SearchAreaBehaviour::Evaluate(Agent* agent)
{
	return 0.05f;
}

//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// GO TO TOILET LOCATION BEHAVIOUR
void Behaviours::GoToToiletBehaviour::Enter(Agent* agent)
{
	if (Game::toiletLocations.size() > 0) {
		Vector2 randLoc = Game::toiletLocations[rand() % Game::toiletLocations.size()];
		agent->pathAgent->GoToNode(agent->pathAgent->parentGraph->GetClosestNode(randLoc));
	}
	isFinished = false;
	toiletDurationCount = 0;
}


void Behaviours::GoToToiletBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->pathAgent->hasFinishedPath) {
		toiletDurationCount += deltaTime;
		if (toiletDurationCount >= toiletDuration) {
			isFinished = true;
			toiletDurationCount = 0;
		}
	}
	
}

float Behaviours::GoToToiletBehaviour::Evaluate(Agent* agent)
{
	return chance;
}


//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
// DEFEND TARGET BEHAVIOUR
void Behaviours::DefendBehaviour::Enter(Agent* agent)
{
}

void Behaviours::DefendBehaviour::Update(Agent* agent, float deltaTime)
{
	if (Evaluate(agent) == 0.0f) {
		isFinished = true;
	}


	cooldownCount += deltaTime;
	if (cooldownCount < cooldown && !agent->pathAgent->hasFinishedPath) {
		return;
	}
	cooldownCount = 0;

	// Check if the agent has moved significantly from its last position
	Agent* target = agentToDefend;

	Vector2 diff = Vector2Subtract(target->pathAgent->ownerPhysics->GetPosition(), lastAgentPosition);
	float dist = Vector2DotProduct(diff, diff);
	float cellSize = agent->pathAgent->parentGraph->m_cellSize;
	if (dist > (cellSize * cellSize))
	{
		lastAgentPosition = target->pathAgent->ownerPhysics->GetPosition();

		// Get random point close to defend target
		Vector2 randDir = { ((rand() % 2000 - 1000) / 1000.0f),((rand() % 2000 - 1000) / 1000.0f) };
		agent->pathAgent->GoTo(Vector2Add(lastAgentPosition, Vector2Scale(randDir, 100)));
	}
}

float Behaviours::DefendBehaviour::Evaluate(Agent* agent)
{

	if (agentToDefend->currentBehaviour->name == "GoToImportant") {
		return 1.0f;
	}
	else if(agentToDefend->currentBehaviour->name == "GoToToilet") {
		return 0.0f;
	}
	else {
		return 0.3f;
	}
	
}
