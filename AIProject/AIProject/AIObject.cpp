#include "AIObject.h"

AIObject::AIObject()
{
	tag = "AI";
	AIAgent = new PathAgent(physics);

	AddToGameWorld();
}

AIObject::~AIObject()
{
	delete AIAgent;
}

void AIObject::Update(float DeltaTime)
{
	AIAgent->Update(DeltaTime);

}

void AIObject::Draw()
{
	AIAgent->DrawPath();
	AIAgent->Draw();
}
