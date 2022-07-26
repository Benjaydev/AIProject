#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	Camera2D camera;

	std::vector<std::string> weapons;


	void Update(float DeltaTime) override;
	void Draw() override;

	virtual void UseWeapon() override;
	virtual void Kill() override;

};

