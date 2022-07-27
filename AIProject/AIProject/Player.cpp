#include "Player.h"
#include "Game.h"
Player::Player() : GameObject()
{
	tag = "Player";

	spriteObject->LoadSprite((char*)"Images/Agent74.png");
	spriteObject->sprite->Scale(0.5f);

	InitSprites();

	physics->SetCollider(cType::Circle);
	((CircleCollider*)physics->collider)->center = physics->GetPosition();
	((CircleCollider*)physics->collider)->radius = 20;

	physics->deceleration = 10;
	physics->moveSpeed = 1000;
	
	AddToGameWorld();


	camera = Camera2D{ {0, 0}, spriteObject->physics->GetPosition(), 0, 1.0f };



	// Setup UI


}

Player::~Player()
{
	spriteObject->isWaitingDestroy = true;
}

void Player::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);

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
	// Take costume
	if (IsKeyPressed(KEY_E)) {
		for (int i = 0; i < Game::objects.size(); i++) {
			if (Game::objects[i]->tag == "AI") {
				// If dead
				if (!((GameObject*)Game::objects[i])->isAlive && ((GameObject*)Game::objects[i])->costume != "Target") {
					// Get distance from dead body
					Vector2 diff = Vector2Subtract(physics->GetPosition(), Game::objects[i]->physics->GetPosition());
					float dist = Vector2DotProduct(diff, diff);

					if (dist <= (30 * 30)) {
						// Change costume
						std::string temp = costume;
						SetCostume(((GameObject*)Game::objects[i])->costume);
						((GameObject*)Game::objects[i])->SetCostume(temp);
					}
					
				}
			}
		}
	}
	if (IsKeyPressed(KEY_ONE)) {
		SetWeapon("");
	}
	if (IsKeyPressed(KEY_TWO)) {
		SetWeapon("Knife");
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		UseWeapon();
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

void Player::UseWeapon()
{
	GameObject::UseWeapon();

	if (weapon == "Knife") {
		CircleCollider* knifeCollider = new CircleCollider();
		Hit out;
		knifeCollider->center = Vector2Add(physics->GetPosition(), Vector2Scale(physics->GetFacingDirection(), 10));
		knifeCollider->SetDiameter(45);
		for (int i = 0; i < AIObject::WorldAIInstances.size(); i++) {
			if (knifeCollider->Overlaps(AIObject::WorldAIInstances[i]->physics->collider, { 0,0,0 }, { 0,0,0 }, out)) {
				AIObject::WorldAIInstances[i]->Kill();
			}
		}
		delete knifeCollider;
	}
}

void Player::Kill() {
	GameObject::Kill();
}