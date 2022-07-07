#include "Player.h"

Player::Player()
{
	tag = "Player";

	spriteObject->LoadSprite((char*)"Images/Agent74.png");
	spriteObject->sprite->SetScale(0.5f);

	physics->SetCollider(cType::Circle);
	((CircleCollider*)physics->collider)->center = physics->GetPosition();
	((CircleCollider*)physics->collider)->radius = 20;

	physics->deceleration = 10;

	AddChild(spriteObject);
	spriteObject->physics->SetRotation(-90 * DEG2RAD);
	spriteObject->physics->SetPosition(-spriteObject->sprite->GetCentreOffset().x, spriteObject->sprite->GetCentreOffset().y);
	

	AddToGameWorld();



	camera = Camera2D{ {0, 0}, spriteObject->physics->GetPosition(), 0, 1.0f };
}

Player::~Player()
{
	spriteObject->isWaitingDestroy = true;
}

void Player::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	//camera.offset = Vector2Subtract(physics->GetPosition(), camera.target);
	camera.target = Vector2Subtract(physics->GetPosition(), {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2});


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

	
	Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);

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
