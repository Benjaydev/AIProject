#pragma once
#include "Object.h"
class Player : public Object
{
public:
	Player();
	virtual ~Player();

	Object* spriteObject = new Object();;



	void Update(float DeltaTime) override;
	void Draw() override;

};

