#pragma once
#include "Behaviour.h"
#include <vector>
using namespace Behaviours;

class UtilityAI : public Behaviour
{
private:
    std::vector<Behaviour*> m_behaviours;
    Behaviour* currentBehaviour;

public:
    UtilityAI();
    ~UtilityAI();

    float cooldown = 3;
    float cooldownCount = 0;

    void AddBehaviour(Behaviour* b);
    virtual void Update(Agent* agent, float deltaTime);

    void DrawBehaviourValue(Agent* agent, int behaviourIndex, float behaviourValue);
    virtual void Draw(Agent* agent);

    int GetIndexOfRandomisedWeights(float* weights, int n);
};

