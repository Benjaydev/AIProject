#include "AIObject.h"
std::vector<AIObject*> AIObject::WorldAIInstances;

AIObject::AIObject(NodeGraph* graph) : GameObject()
{
	WorldAIInstances.push_back(this);
	AIInstanceID = WorldAIInstances.size() - 1;

	tag = "AI";

    physics->SetCollider(cType::Circle);
    ((CircleCollider*)physics->collider)->center = physics->GetPosition();
    ((CircleCollider*)physics->collider)->radius = 20;

    CreateAIAgent();
    AIAgent->pathAgent->SetParentGraph(graph);

	AddToGameWorld();

    physics->deceleration = 10;
    physics->moveSpeed = 1000;


}

AIObject::~AIObject()
{
	delete AIAgent;
}

void AIObject::CreateAIAgent(Behaviour* beaviour)
{
	AIAgent = new Agent(beaviour);
	AIAgent->CreatePathAgent(physics);
}
void AIObject::CreateAIAgent()
{
	AIAgent = new Agent();
	AIAgent->CreatePathAgent(physics);
}

void AIObject::Update(float DeltaTime)
{
    Object::Update(DeltaTime);
	AIAgent->Update(DeltaTime);

}

void AIObject::Draw()
{
    Object::Draw();
	AIAgent->Draw();
}
