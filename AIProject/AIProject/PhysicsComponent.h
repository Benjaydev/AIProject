#pragma once
#include <iostream>
#include <vector>
#include "Collider.h"

class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	// Movement values
	float maxSpeed = 200.0f;
	float moveSpeed = 100.0f;
	Vector3* velocity = new Vector3();
	Vector3 deltaVelocity(float DeltaTime) {
		return { velocity->x * DeltaTime, velocity->y * DeltaTime, velocity->z * DeltaTime };
	}
	Vector3* acceleration = new Vector3();
	float deceleration = 0.01f;
	Vector2 LockAxis = { 0, 0 };

	// Transformation matrices
	Matrix localTransform = Matrix();
	Matrix globalTransform = Matrix();

	// Referenced physics components
	PhysicsComponent* parentPhysics = nullptr;
	std::vector<PhysicsComponent*> childrenPhysics;

	// Collisions
	Collider* collider;
	bool isColliding = false;
	bool hasPhysicsCheck = true;
	void SetCollider(cType type);
	void FitColliderWH(float width, float height, Vector2 pos);
	// Collision check
	static void GlobalCollisionCheck(float DeltaTime, bool shouldCullOffScreenObjects = true);

	void Update(float DeltaTime);
	void UpdateTransform();
	void Translate(float x, float y);
	void Translate(Vector2 v);

	// Movement functions
	void AccelerateFacing(float direction);
	void AccelerateFacingRotated(float direction, float degrees);
	void AccelerateInDirection(Vector2 direction);
	void Decelerate(float DeltaTime);
	void CalculateVelocity(float DeltaTime);
	void Move(float DeltaTime);

	void SetPosition(float x, float y);
	Vector2 GetPosition() {
		return { globalTransform.m8, globalTransform.m9 };
	}
	Vector2 GetFacingDirection() {
		return { globalTransform.m0, globalTransform.m1 };
	}
	void SetFacing(Vector2 facing) {
		localTransform.m0 = facing.x;
		localTransform.m1 = facing.y;
		UpdateTransform();
	}
	void SetPosition(Vector2 v);
	void SetRotation(float zRad);
	void Rotate(float rad);

	// Helper maths functions
	static Vector3 Vector3FloatMultiply(Vector3 v1, float f);
	static Vector3 Vector3FloatDivision(Vector3 v1, float f);
	


};

