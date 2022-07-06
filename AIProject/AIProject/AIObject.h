#pragma once
#include "Agent.h"
#include "Object.h"
#include "FiniteStateMachine.h"

class AIObject : public Object
{
public:
	AIObject(NodeGraph* graph);
	virtual ~AIObject();


	void CreateAIAgent(FiniteStateMachine* fsm);
	void CreateAIAgent();
	Agent* AIAgent;

	void Update(float DeltaTime) override;
	void Draw() override;

};

