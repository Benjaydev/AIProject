#pragma once
#include "Object.h"
class Map : public Object
{

public:
	Map();
	virtual ~Map();


	void Update(float DeltaTime) override;
	virtual void DrawBackground() = 0;
};

