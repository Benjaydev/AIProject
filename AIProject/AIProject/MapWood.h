#pragma once
#include "Map.h"
class MapWood : Map
{
public:
	MapWood();
	virtual ~MapWood();


	Texture2D floorBackground;
	Texture2D grassBackground;

	Vector2 BackgroundStartOffset = {-2000, -1600};


	void Update(float DeltaTime) override;
	void DrawBackground() override;
};

