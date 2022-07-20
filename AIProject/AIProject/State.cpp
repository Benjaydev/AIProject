#include "State.h"

State::~State()
{
    // we own the behaviours assigned to us
    for (Behaviour* b : m_behaviours) {
        delete b;
    }

    // we also own the Conditions in each Transition
        // (but the states are references, so don’t clean them up here)
    for (Transition t : m_transitions) {
        delete t.condition;
    }
}

void State::Enter(Agent* agent)
{
}

void State::Update(Agent* agent, float deltaTime)
{
    for (Behaviour* b : m_behaviours) {
        b->Update(agent, deltaTime);
        b->Draw(agent);
    }
        
}

void State::Exit(Agent* agent)
{
}

void State::AddTransition(Condition* condition, State* state)
{
    Transition trans = Transition();
    trans.condition = condition;
    trans.targetState = state;
    m_transitions.push_back(trans);
}
