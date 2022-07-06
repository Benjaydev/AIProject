#pragma once
#include "raymath.h"
#include <string>

// Structure for storing hit result data
struct Hit {
	Vector3 OutVel = Vector3();
	Vector2 HitNormal = Vector2();
	Vector2 HitPoint = Vector2();
	float percentDistanceAlongHitFace = -1;
	std::string otherTag = "";
	
};

