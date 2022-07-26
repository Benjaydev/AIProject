#pragma once
#include "Agent.h"
#include "GameObject.h"


class AIObject : public GameObject
{
public:
	AIObject(NodeGraph* graph);
	virtual ~AIObject();



	void CreateAIAgent(Behaviour* beaviour);
	void CreateAIAgent();
	Agent* AIAgent;

	void Update(float DeltaTime) override;
	void Draw() override;

	int AIInstanceID = 0;
	static std::vector<AIObject*> WorldAIInstances;

	virtual void UseWeapon() override;
	virtual void Kill() override;
};

