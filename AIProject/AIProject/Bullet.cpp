#include "Bullet.h"

Bullet::Bullet(Vector2 position, Vector2 direction)
{
	tag = "Bullet";
	spriteObject->LoadSprite((char*)"Images/Bullet.png");
	spriteObject->physics->SetRotation(-90 * DEG2RAD);
	spriteObject->physics->SetPosition(-spriteObject->sprite->GetCentreOffset().x, spriteObject->sprite->GetCentreOffset().y);
	spriteObject->sprite->Scale(0.5f);
	AddChild(spriteObject);

	physics->SetFacing(direction);
	physics->SetPosition(position);

	physics->SetCollider(cType::Circle);
	((CircleCollider*)physics->collider)->center = physics->GetPosition();
	((CircleCollider*)physics->collider)->radius = 5;

	physics->deceleration = 0;
	physics->moveSpeed = 10000;
	physics->maxSpeed = 10000;

	AddToGameWorld();
}

Bullet::~Bullet()
{
	delete spriteObject;
}

void Bullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	physics->AccelerateFacing(1);

	lifetime -= DeltaTime;
	if (lifetime <= 0) {
		DeleteSelf();
	}
}

void Bullet::Draw()
{
	Object::Draw();
}
