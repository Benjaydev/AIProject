#pragma once
#include "Object.h"
class Bullet : public Object
{
public:
	Bullet(Vector2 position, Vector2 direction);
	virtual ~Bullet();

	Object* spriteObject = new Object();

	float lifetime = 3;

	void Update(float DeltaTime) override;
	void Draw() override;
};

