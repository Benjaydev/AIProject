#include "Player.h"

Player::Player()
{
	tag = "Player";

	spriteObject->LoadSprite((char*)"Images/PlayerCounter.png");

	physics->SetCollider(cType::Circle);
	((CircleCollider*)physics->collider)->center = physics->GetPosition();
	((CircleCollider*)physics->collider)->radius = 20;

	physics->deceleration = 10;

	AddChild(spriteObject);
	spriteObject->physics->SetRotation(-90 * DEG2RAD);
	spriteObject->physics->SetPosition(-spriteObject->sprite->GetCentreOffset().x, spriteObject->sprite->GetCentreOffset().y);
	

	AddToGameWorld();


}

Player::~Player()
{
	spriteObject->isWaitingDestroy = true;
}

void Player::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	if (IsKeyDown(KEY_W)) {
		physics->AccelerateInDirection({ 0, -1 });
	}
	if (IsKeyDown(KEY_A)) {
		physics->AccelerateInDirection({ -1, 0 });
	}
	if (IsKeyDown(KEY_S)) {
		physics->AccelerateInDirection({ 0, 1 });
	}
	if (IsKeyDown(KEY_D)) {
		physics->AccelerateInDirection({ 1, 0 });
	}

	Vector2 mousePos = GetMousePosition();

	Vector2 dir = Vector2Subtract(mousePos, physics->GetPosition());
	float angle = acosf(Vector2DotProduct(physics->GetFacingDirection(), Vector2Normalize(dir)));
	
	if (abs(angle) > 0.1) {
		physics->Rotate(angle);
	}
	

}

void Player::Draw()
{
	Object::Draw();
}
