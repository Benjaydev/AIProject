#include "Agent.h"


Agent::Agent()
{

}

Agent::Agent(Behaviour* _behaviour)
{
	currentBehaviour = _behaviour;
    currentBehaviour->Enter(this);
}

void Agent::Update(float deltaTime)
{
    if (currentBehaviour != nullptr) {
        currentBehaviour->Update(this, deltaTime);
    }
    pathAgent->Update(deltaTime);
}

void Agent::Draw()
{
    pathAgent->DrawPath();

    Vector2 pos = pathAgent->ownerPhysics->GetPosition();
    DrawCircle((int)pos.x, (int)pos.y, 8 * (pathAgent->GetParentCellSize() / 50), m_colour);
    
}

void Agent::SetBehaviour(Behaviour* behaviour)
{
    currentBehaviour = behaviour;
}

void Agent::FaceTarget()
{
    Vector2 angleDiff = Vector2Normalize(Vector2Subtract(target->physics->GetPosition(), pathAgent->ownerPhysics->GetPosition()));
    float angle = atan2(angleDiff.x, angleDiff.y) - atan2(pathAgent->ownerPhysics->GetFacingDirection().x, pathAgent->ownerPhysics->GetFacingDirection().y);
    if (angle > PI) { angle -= 2 * PI; }
    else if (angle <= -PI) { angle += 2 * PI; }

    pathAgent->ownerPhysics->Rotate(angle);

}
