#pragma once
#include "Behaviour.h"
#include "State.h"
using namespace Behaviours;



class FiniteStateMachine : public Behaviour
{
private:
    std::vector<State*> m_states;

    State* m_currentState;
    State* m_newState;

public:
    FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) {}
    virtual ~FiniteStateMachine();

    void AddState(State* state);

    virtual void Enter(Agent* agent);
    void Update(Agent* agent, float deltaTime);
    virtual void Draw(Agent* agent);
};