#include "Player.h"

Player::Player() : GameObject()
{
	tag = "Player";

	spriteObject->LoadSprite((char*)"Images/Agent74.png");
	spriteObject->sprite->SetScale(0.5f);


	InitSprites();

	physics->SetCollider(cType::Circle);
	((CircleCollider*)physics->collider)->center = physics->GetPosition();
	((CircleCollider*)physics->collider)->radius = 20;

	physics->deceleration = 10;
	physics->moveSpeed = 1000;
	

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
	if (IsKeyPressed(KEY_ONE)) {
		SetWeapon("");
	}
	if (IsKeyPressed(KEY_TWO)) {
		SetWeapon("Pistol");
	}

	
	Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);

	Vector2 dir = Vector2Subtract(mousePos, physics->GetPosition());
	float angle = atan2(dir.x, dir.y) - atan2(physics->GetFacingDirection().x, physics->GetFacingDirection().y);
	
	if (abs(angle) > 0.1) {
		physics->Rotate(angle);
	}
	

}

void Player::Draw()
{
	Object::Draw();
}
