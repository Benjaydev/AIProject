#pragma once
#include "Agent.h"
#include "Object.h"


class AIObject : public Object
{
public:
	AIObject(NodeGraph* graph);
	virtual ~AIObject();

	Object* spriteObject = new Object();


	void CreateAIAgent(Behaviour* beaviour);
	void CreateAIAgent();
	Agent* AIAgent;

	void Update(float DeltaTime) override;
	void Draw() override;

};

