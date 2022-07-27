#include "FiniteStateMachine.h"

FiniteStateMachine::~FiniteStateMachine()
{
    // the FSM owns every State assigned to it
    for (State* s : m_states)
        delete s;
}

void FiniteStateMachine::AddState(State* state)
{
    m_states.push_back(state);
}

void FiniteStateMachine::Update(Agent* agent, float deltaTime)
{
    State* newState = nullptr;

    // check the current state's transitions
    for (State::Transition t : m_currentState->GetTransitions())
    {
        if (t.condition->IsTrue(agent, deltaTime) == t.ifConditionIs) {
            newState = t.targetState;
        }
            
    }

    // Clean up the old one and initialise the new one
    if (newState != nullptr)
    {
        m_currentState->Exit(agent);
        m_currentState = newState;

        m_currentState->Enter(agent);
    }

    // update the current state
    m_currentState->Update(agent, deltaTime);
    name = m_currentState->GetBehaviourName(0);
}

void FiniteStateMachine::Draw(Agent* agent)
{
    if (m_currentState != nullptr) {
        m_currentState->Draw(agent);
    }
    
}

void FiniteStateMachine::Enter(Agent* agent)
{
    m_currentState->Enter(agent);
}