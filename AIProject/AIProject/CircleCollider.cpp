#include "Collider.h"
#include <iostream>
using namespace std;

CircleCollider::CircleCollider()
{
	// Set type
	type = cType::Circle;
}
// Construct from point and radius
CircleCollider::CircleCollider(Vector2 point, float r)
{
	center = point;
	radius = r;
	type = cType::Circle;
}
// Copy constructor
CircleCollider::CircleCollider(CircleCollider* copy)
{
	center = Vector2(copy->center);
	radius = copy->radius;
	type = cType::Circle;
}

// Destructor
CircleCollider::~CircleCollider()
{
}

void CircleCollider::DrawDebug()
{
	// Draw circle to represent collider
	DrawCircleLines(center.x, center.y, radius, RED);
}

// Fit collider to set of points in vector data structure
void CircleCollider::Fit(std::vector<Vector3> points)
{
	// Invalidate extents 
	Vector3 min = Vector3({ FLT_MAX, FLT_MAX, FLT_MAX });
	Vector3 max = Vector3({FLT_MIN, FLT_MIN, FLT_MIN});

	// Find min and max of the points 
	for (int i = 0; i < points.size(); ++i)
	{
		min = Vector3Min(min, points[i]);
		max = Vector3Max(max, points[i]);
	}

	// Put a circle around the min/max box 
	Vector3 add = Vector3Add(min, max);
	center = {add.x*0.5f, add.y*0.5f};
	radius = Vector3Length(Vector3Subtract(max, { center.x, center.y }));
}

// Fit collider to set of points in array data structure
void CircleCollider::Fit(Vector3 points[])
{
	// Invalidate extents 
	Vector3 min = Vector3({ FLT_MAX, FLT_MAX, FLT_MAX });
	Vector3 max = Vector3({ FLT_MIN, FLT_MIN, FLT_MIN });

	// Find min and max of the points 
	for (int i = 0; i < sizeof(points)/sizeof(Vector3); ++i)
	{
		min = Vector3Min(min, points[i]);
		max = Vector3Max(max, points[i]);
	}

	// Put a circle around the min/max box 
	Vector3 add = Vector3Add(min, max);
	center = { add.x * 0.5f, add.y * 0.5f };
	radius = Vector3Length(Vector3Subtract(max, { center.x, center.y }));
}

bool CircleCollider::Overlaps(Vector2 point)
{
	// Check if point overlaps this circle collider
	Vector2 p = Vector2Subtract(point, center);
	return Vector2DotProduct(p, p) <= (radius * radius);;
}

bool CircleCollider::Overlaps(Collider* other, Vector3 thisVel, Vector3 otherVel, Hit& result)
{
	// Get relative velocity between this collider and other collider
	Vector3 relVel = Vector3Subtract(thisVel, otherVel);

	// If other collider is a rectangle
	if (other->type == cType::Rectangle) {
		// Cast other object to rectangle
		RectangleCollider* rec = (RectangleCollider*)other;

		// Get closest point on rectangle to center of circle at future relative location
		Vector2 closest = rec->ClosestPoint({ center.x+thisVel.x, center.y + thisVel.y });

		// If overlaps
		if (Overlaps(closest)) {
			// Find the intersection depth
			result.OutVel = thisVel;
			Vector2 diff = Vector2Subtract(closest, { center.x + thisVel.x, center.y + thisVel.y });
			Vector2 normDiff = Vector2Normalize(diff);
			float dist = Vector2Length(diff);
			float rCheck = radius - dist;

			// Return the correction velocity
			result.OutVel.x = -(normDiff.x*rCheck);
			result.OutVel.y = -(normDiff.y * rCheck);


			// Calculate the normal
			if (closest.x == rec->min.x) {
				result.HitNormal.x = -1;
			}
			if (closest.y == rec->min.y) {
				result.HitNormal.y = -1;
			}

			if (closest.x == rec->max.x) {
				result.HitNormal.x = 1;
			}
			if (closest.y == rec->max.y) {
				result.HitNormal.y = 1;
			}

		

			// Get at what percentage on the face is the collision (Left to right, 0 to 1)
			// Top and bottom face
			if ((result.HitNormal.x == 0 && result.HitNormal.y == -1) || (result.HitNormal.x == 0 && result.HitNormal.y == 1)) {
				result.percentDistanceAlongHitFace = ( ((closest.x - rec->min.x) * 100) / (rec->max.x - rec->min.x))/100;
			}
			// Right and left face
			else if ((result.HitNormal.x == 1 && result.HitNormal.y == 0) || (result.HitNormal.x == -1 && result.HitNormal.y == 0)) {
				result.percentDistanceAlongHitFace = (((closest.y - rec->min.y) * 100) / (rec->max.y - rec->min.y)) / 100;
			}
			return true;
		}

		return false;
	}
	// If other collider is circle
	else if (other->type == cType::Circle) {
		// Cast other collider to circle collider
		CircleCollider* cir = (CircleCollider*)other;

		// Find difference between both circles at future point
		Vector2 diff = Vector2Subtract(cir->center, { center.x + relVel.x, center.y + relVel.y });
		result.HitNormal = Vector2Normalize(diff);

		float diffLength = Vector2Length(diff);
		float r = radius + cir->radius;

		// Calculate the correction velocity
		result.OutVel.x = result.HitNormal.x * diffLength;
		result.OutVel.y = result.HitNormal.y * diffLength;

		return Vector2DotProduct(diff, diff) <= (r * r);

		
	}
	
}


void CircleCollider::Translate(float x, float y)
{
	center.x += x;
	center.y += y;
}
