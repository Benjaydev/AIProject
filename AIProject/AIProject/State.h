#pragma once
#include <vector>
#include "Behaviour.h"
#include "Condition.h" 
using namespace Behaviours;
using namespace Conditions;

class State
{
public:
    struct Transition
    {
        Condition* condition;
        State* targetState;
        bool ifConditionIs = true;
    };
private:
    std::vector<Behaviour*> m_behaviours;
    std::vector<Transition> m_transitions;

public:
    State(Behaviour* behaviour) {
        m_behaviours.push_back(behaviour);
    };
    ~State();

    virtual void Enter(Agent* agent);
    virtual void Update(Agent* agent, float deltaTime);
    virtual void Exit(Agent* agent);

    virtual void Draw(Agent* agent);

    void AddTransition(Condition* condition, State* state, bool ifConditionIs = true);


    std::string GetBehaviourName(int index) {
        return m_behaviours[index]->name;
    }

    std::vector<Transition> GetTransitions() {
        return m_transitions;
    }
};
