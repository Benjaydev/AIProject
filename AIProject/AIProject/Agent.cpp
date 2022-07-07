#include "Agent.h"


Agent::Agent()
{

}

Agent::Agent(Behaviour* _behaviour)
{
	m_current = _behaviour;
    m_current->Enter(this);
}

void Agent::Update(float deltaTime)
{
    if (m_current != nullptr) {
        m_current->Update(this, deltaTime);
    }
    m_pathAgent->Update(deltaTime);
}

void Agent::Draw()
{
    m_pathAgent->DrawPath();

    Vector2 pos = m_pathAgent->ownerPhysics->GetPosition();
    DrawCircle((int)pos.x, (int)pos.y, 8 * (m_pathAgent->GetParentCellSize() / 50), m_colour);
    
}

void Agent::SetBehaviour(Behaviour* behaviour)
{
    m_current = behaviour;
}
