#include "Collider.h"
#include <iostream>

using namespace std;

Collider::Collider()
{
}

Collider::~Collider()
{
}

// Create copy of collider
Collider* Collider::Copy(Collider* copy)
{
	// Create copy of rectangle collider
	if (copy->type == cType::Rectangle) {
		return new RectangleCollider((RectangleCollider*)copy);
	}
	// Create copy of circle collider
	else if (copy->type == cType::Circle) {
		return new CircleCollider((CircleCollider*)copy);
	}
}

/*
// Check if collider overlaps screen borders
bool Collider::OverlapsScreen(Vector3 velocity, Hit& result)
{
	// If the collider is a rectangle
	if (type == cType::Rectangle) {
		// Cast to rectangle collider
		RectangleCollider* rec = (RectangleCollider*)this;

		result.OutVel = velocity;

		// Calculate which wall is hit and the normal
		// Left wall
		if (rec->min.x + velocity.x < Game::WorldBorders.x) {
			result.HitNormal.x = 1;
			result.OutVel.x = velocity.x + (Game::WorldBorders.x - (rec->min.x + velocity.x));
		}
		// Top Wall
		if (rec->min.y + velocity.y < Game::WorldBorders.y) {
			result.HitNormal.y = 1;
			result.OutVel.y = velocity.y +(Game::WorldBorders.y - (rec->min.y + velocity.y));
		}
		// Right wall
		if (rec->max.x + velocity.x > Game::WorldBorders.z) {
			result.HitNormal.x = -1;
			result.OutVel.x = velocity.x + (Game::WorldBorders.z - (rec->max.x + velocity.x));
		}
		// Bottom wall
		if (rec->max.y+ velocity.y > Game::WorldBorders.w) {
			result.HitNormal.y = -1;
			result.OutVel.y = velocity.y + (Game::WorldBorders.w - (rec->max.y + velocity.y));
		}

		// If it has hit a wall
		if (result.HitNormal.x != 0 || result.HitNormal.y != 0) {
			return true;
		}
	}
	// If collider type is circle
	else if (type == cType::Circle) {
		// Cast to circle collider
		CircleCollider* cir = (CircleCollider*)this;

		result.OutVel = velocity;

		Vector3 normVelocity = Vector3Normalize(velocity);

		// Calculate which wall is hit and the normal
		// Left wall
		if ((cir->center.x + velocity.x) + normVelocity.x*cir->radius < Game::WorldBorders.x) {
			result.HitNormal.x = 1;
			result.OutVel.x =  (velocity.x - (Game::WorldBorders.y - (cir->center.x + velocity.x))) - (normVelocity.x * cir->radius);
		}
		// Top wall
		if ((cir->center.y + velocity.y) + normVelocity.y * cir->radius < Game::WorldBorders.y) {
			result.HitNormal.y = 1;
			result.OutVel.y =  (velocity.y - (Game::WorldBorders.y - (cir->center.y + velocity.y))) - (normVelocity.y * cir->radius);
		}
		// Right wall
		if ((cir->center.x + velocity.x) + normVelocity.x * cir->radius > Game::WorldBorders.z) {
			result.HitNormal.x = -1;
			
			result.OutVel.x =  (velocity.x + (Game::WorldBorders.z - (cir->center.x + velocity.x))) - (normVelocity.x * cir->radius);
		}
		// Bottom wall
		if ((cir->center.y + velocity.y) + normVelocity.y * cir->radius > Game::WorldBorders.w) {
			result.HitNormal.y = -1;
			result.OutVel.y = (velocity.y + (Game::WorldBorders.w - (cir->center.y + velocity.y))) - (normVelocity.y * cir->radius);
		}

		// If has hit a wall
		if (result.HitNormal.x != 0 || result.HitNormal.y != 0) {
			return true;
		}
	}

	return false;
}
*/