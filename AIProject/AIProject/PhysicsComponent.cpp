#pragma once
#include "PhysicsComponent.h"
#include "raymath.h"
#include "Game.h"


using namespace std;

PhysicsComponent::PhysicsComponent()
{
	localTransform = MatrixIdentity();
	globalTransform = MatrixIdentity();
}

PhysicsComponent::~PhysicsComponent()
{
	// Delete collider if valid
	if (collider != nullptr) {
		delete collider;
	}
	// Delete movement values
	delete velocity;
	velocity = nullptr;
	delete acceleration;
	acceleration = nullptr;

	// Remove parent physics
	delete parentPhysics;

	// Clear children physics vector
	childrenPhysics.clear();
}

void PhysicsComponent::SetCollider(cType type)
{
	// Set collider type of this physics component
	if (type == cType::Rectangle) {
		collider = new RectangleCollider();
	}
	else if (type == cType::Circle) {
		collider = new CircleCollider();
	}
}

// Fit attached collider to width and height (Usually used with sprites)
void PhysicsComponent::FitColliderWH(float width, float height, Vector2 pos)
{
	if (collider != nullptr) {
		std::vector<Vector3> points = { {pos.x - (width / 2), pos.y - (height / 2), 0 }, {pos.x + (width / 2), pos.y + (height / 2), 0 } };
		collider->Fit(points);
	}
	
}

void PhysicsComponent::Update(float DeltaTime)
{
	CalculateVelocity(DeltaTime);
}

void PhysicsComponent::UpdateTransform()
{
	Vector2 lastpos = { globalTransform.m8, globalTransform.m9 };

	// Calculate global transform if this object has parent transform
	if (parentPhysics != nullptr) {
		globalTransform = MatrixMultiply(localTransform, parentPhysics->globalTransform);
	}
	// Default to using local transform
	else {
		globalTransform = localTransform;
	}

	// Update transform for every child physics component
	for (int i = 0; i < childrenPhysics.size(); i++) {
		childrenPhysics[i]->UpdateTransform();
	}


	// Update collider position
	if (collider != nullptr) {
		// Translate by difference between points
		collider->Translate(globalTransform.m8- lastpos.x,  globalTransform.m9- lastpos.y);
	}
	
}


void PhysicsComponent::AccelerateFacing(float direction)
{
	Vector3 facing = { localTransform.m0, localTransform.m1, 1};
	
	// Get travel distance fowards
	facing = Vector3FloatMultiply(facing, moveSpeed * direction);

	// Add to acceleration
	*acceleration = Vector3Add(*acceleration, facing);
}

void PhysicsComponent::AccelerateFacingRotated(float direction, float degrees)
{
	Vector2 dir = Vector2Rotate({ localTransform.m0, localTransform.m1 }, degrees);
	Vector3 facing = { dir.x, dir.y, 1 };

	// Get travel distance fowards
	facing = Vector3FloatMultiply(facing, moveSpeed * direction);

	// Add to acceleration
	*acceleration = Vector3Add(*acceleration, facing);
}

void PhysicsComponent::AccelerateInDirection(Vector2 direction)
{
	Vector3 facing = { direction.x, direction.y, 1 };

	// Get travel distance
	facing = Vector3FloatMultiply(facing, moveSpeed);

	// Add to acceleration
	*acceleration = Vector3Add(*acceleration, facing);
}

void PhysicsComponent::Decelerate(float DeltaTime)
{
	// Lower velocity
	*velocity = Vector3FloatMultiply(*velocity, 1-(deceleration * DeltaTime));
}

void PhysicsComponent::CalculateVelocity(float DeltaTime)
{
	// Add the acceleration to the veocity
	*velocity = Vector3Add(*velocity, *acceleration);

	// Decelerate velocity for this frame
	Decelerate(DeltaTime);


	// Keep velocity within max speed //
	float mag = Vector3Length(*velocity);
	if (mag != 0) {
		// Normalise direction
		Vector3 norm = Vector3FloatDivision(*velocity, mag);
		// Cap the speed at max speed for velocity
		float speed = fminf(mag, maxSpeed);
		// Set velocity to the speed
		*velocity = Vector3FloatMultiply(norm, speed);
	}
	
	// Reset the acceleration
	acceleration->x = 0;
	acceleration->y = 0;
	acceleration->z = 0;

}

// Move the transform
void PhysicsComponent::Move(float DeltaTime)
{
	// If collider has a parent, apply the forces to the parent instead
	if (parentPhysics != nullptr) {
		if (parentPhysics->velocity != nullptr) {

			// Add forces to parent
			parentPhysics->velocity->x += velocity->x;
			parentPhysics->velocity->y += velocity->y;

			// Remove forces from this
			velocity->x = 0;
			velocity->y = 0;
			return;
		}
	}

	// If axes are locked, do not move
	if (LockAxis.x && LockAxis.y) {
		return;
	}

	// Get velocity capped at max speed
	//velocity->x = fminf(velocity->x, maxSpeed);
	//velocity->y = fminf(velocity->y, maxSpeed);

	// Locked x axis
	if (!LockAxis.x && LockAxis.y) {
		Translate(velocity->x * DeltaTime,0);
		return;
	}
	// Locked y axis
	if (LockAxis.x && !LockAxis.y) {
		Translate(0, velocity->y * DeltaTime);
		return;
	}

	// Translate on both axes
	Translate(velocity->x * DeltaTime, velocity->y * DeltaTime);
}


void PhysicsComponent::Translate(float x, float y) {
	// Add values to global transform position
	localTransform.m8 += x;
	localTransform.m9 += y;
	
	// Apply changes
	UpdateTransform();
}

// Translate using Vector2
void PhysicsComponent::Translate(Vector2 v)
{
	Translate(v.x, v.y);
}

// Set position using differences instead of directly so that children or parent physics can be updated correctly
void PhysicsComponent::SetPosition(float x, float y)
{
	// Find the difference between locations and translate along that
	float diffx = x - localTransform.m8;
	float diffy = y - localTransform.m9;
	Translate(diffx, diffy);
}

void PhysicsComponent::SetPosition(Vector2 v)
{
	// Find the difference between locations and translate along that
	float diffx = v.x - localTransform.m8;
	float diffy = v.y - localTransform.m9;
	Translate(diffx, diffy);
}

void PhysicsComponent::SetRotation(float zRad)
{
	// Create new matrix equal to the new rotation
	Matrix m = MatrixMultiply(MatrixIdentity(), MatrixRotateZ(zRad));
	// Set the transform to the new matrix
	localTransform = m;
	UpdateTransform();
}

void PhysicsComponent::Rotate(float rad) {
	// Rotate current transform
	localTransform = MatrixMultiply(MatrixRotateZ(rad), localTransform);
	UpdateTransform();
}


Vector3 PhysicsComponent::Vector3FloatMultiply(Vector3 v1, float f){
	Vector3 v3 = { v1.x * f, v1.y * f, v1.z * f };
	return v3;
}

Vector3 PhysicsComponent::Vector3FloatDivision(Vector3 v1, float f){
	Vector3 v3 = { v1.x/ f, v1.y / f, v1.z / f };
	return v3;
}


void PhysicsComponent::GlobalCollisionCheck(float DeltaTime)
{
	for (int i = 0; i < Game::objects.size(); i++) {
		// Get the first object to check against the next 
		Object* check = Game::objects[i];

		// If it has no collider or shouldn't check physics, ignore collisions and move
		if (check->physics->collider == nullptr || !check->physics->hasPhysicsCheck) {
			check->physics->Move(DeltaTime);
			continue;
		}
		
		Hit wallResult;
		// Check if object is colliding with screen boundries
		if (check->physics->collider->OverlapsScreenBorders(check->physics->deltaVelocity(DeltaTime), wallResult)) {
			// Set velocity to the adjusted velocity (Removes DeltaTime as it will be applied again during Move(DeltaTime)
			check->physics->velocity->x = wallResult.OutVel.x / DeltaTime;
			check->physics->velocity->y = wallResult.OutVel.y / DeltaTime;
		}


		for (int j = i+1; j < Game::objects.size(); j++) {
			// Get second object to check against the previous object
			Object* against = Game::objects[j];

			// Don't check collision if object does not have physics checks, is child of the other object, if object collider is null, or if both objects have no velocity
			if (!against->physics->hasPhysicsCheck || against->parent == check || against->physics->collider == nullptr || ((check->physics->velocity->x == 0.0f && check->physics->velocity->y == 0.0f) && (against->physics->velocity->x == 0.0f && against->physics->velocity->y == 0.0f))) {
				continue;
			}

			// Do base collision check
			Hit result;
			bool collided = check->physics->collider->Overlaps(against->physics->collider, check->physics->deltaVelocity(DeltaTime), against->physics->deltaVelocity(DeltaTime), result);

			// If collision is detected
			if (collided) {
				if (check->tag == "Player" && against->tag == "Obstacle") {
					// Save tag of other object
					result.otherTag = against->tag;

					// Set velocity to the collision adjusted velocity (Removes DeltaTime as it will be applied again during Move(DeltaTime)
					check->physics->velocity->x = result.OutVel.x / DeltaTime;
					check->physics->velocity->y = result.OutVel.y / DeltaTime;
					check->physics->Move(DeltaTime);

					// Call collide event for first object
					check->CollideEvent(result, against);

				}
				if (check->tag == "Obstacle" && against->tag == "Player") {
					// Save tag of other object
					result.otherTag = check->tag;

					// Set velocity to the collision adjusted velocity (Removes DeltaTime as it will be applied again during Move(DeltaTime)
					against->physics->velocity->x = result.OutVel.x / DeltaTime;
					against->physics->velocity->y = result.OutVel.y / DeltaTime;
					against->physics->Move(DeltaTime);

					// Call collide event for second object
					against->CollideEvent(result, check);

				}


			}
		}
		check->physics->Move(DeltaTime);
		
	}

}
