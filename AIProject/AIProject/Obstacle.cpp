#include "Obstacle.h"

Obstacle::Obstacle()
{
    tag = "Obstacle";
}

Obstacle::~Obstacle()
{
}

void Obstacle::InitiateObstacle(float x, float y)
{
    physics->SetPosition(x, y);
    physics->hasPhysicsCheck = true;
    physics->SetCollider(cType::Rectangle);
    Vector2 pos = physics->GetPosition();
    physics->collider->Fit({ {pos.x, pos.y, 0}, {pos.x + sprite->GetWidth(), pos.y + sprite->GetHeight(), 0} });

    AddToGameWorld();
}

void Obstacle::Update(float DeltaTime)
{
    Object::Update(DeltaTime);
}
