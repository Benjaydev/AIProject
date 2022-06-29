#include "Collider.h"
#include <string>
using namespace std;

RectangleCollider::RectangleCollider() {
	type = cType::Rectangle;
}

RectangleCollider::RectangleCollider(Vector3 otherMin, Vector3 otherMax)
{
	min = otherMin;
	max = otherMax;
	type = cType::Rectangle;
}

// Copy constructor
RectangleCollider::RectangleCollider(RectangleCollider* copy)
{
	RectangleCollider* rec = (RectangleCollider*)copy;
	min = Vector3(rec->min);
	max = Vector3(rec->max);
	type = cType::Rectangle;
}

// Destructor
RectangleCollider::~RectangleCollider() {
	Empty();
}


void RectangleCollider::Translate(float x, float y)
{
	// Translate each min and max axes by values
	min.x += x;
	max.x += x;
	min.y += y;
	max.y += y;
}

Vector3 RectangleCollider::Center()
{
	// Get center of rectangle
	Vector3 center = Vector3Add(min, max);
	center.x *= 0.5f;
	center.y *= 0.5f;
	center.z *= 0.5f;
	return center;

}

void RectangleCollider::DrawDebug()
{
	std::vector<Vector3> c = GetCorners();

	// Draw position
	std::string str = std::to_string(min.x) + ", " + std::to_string(min.y);
	DrawText(str.c_str(), (int)c[0].x-20, (int)c[0].y-20, 12, BLUE);

	// Draw rectangle sides
	DrawLine((int)c[0].x, (int)c[0].y, (int)c[1].x, (int)c[1].y, RED);
	DrawLine((int)c[1].x, (int)c[1].y, (int)c[2].x, (int)c[2].y, RED);
	DrawLine((int)c[2].x, (int)c[2].y, (int)c[3].x, (int)c[3].y, RED);
	DrawLine((int)c[3].x, (int)c[3].y, (int)c[0].x, (int)c[0].y, RED);

	// Draw corners
	DrawCircle((int)c[0].x, (int)c[0].y, 3, VIOLET);
	DrawCircle((int)c[3].x, (int)c[3].y, 3, GREEN);
	DrawCircle((int)c[1].x, (int)c[1].y, 3, BLUE);
	DrawCircle((int)c[2].x, (int)c[2].y, 3, ORANGE);

	// Draw center
	Vector3 center = Center();
	DrawCircle(center.x, center.y, 4, RED);
}

bool RectangleCollider::IsEmpty()
{
	// Check if empty (Empty is when all values are infinite)
	return (isinf(min.x) && isinf(min.y) && isinf(min.z) && isinf(max.x) && isinf(max.y) && isinf(max.z));
}

void RectangleCollider::Empty()
{
	// Set collider to empty (Empty is when all values are infinite)
	boundries[0] = { -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity() };
	boundries[1] = { std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() };
}

void RectangleCollider::Fit(std::vector<Vector3> points)
{
	// Reset the collider
	Empty();

	min = points[0];
	max = points[0];

	// Find min and max between each point and current min and max
	for (int i = 0; i < points.size(); i++) {
		min = Vector3Min(min, points[i]);
		max = Vector3Max(max, points[i]);
	}
}

void RectangleCollider::Fit(Vector3 points[])
{
	// Reset the collider
	Empty();

	min = points[0];
	max = points[0];

	// Find min and max between each point and current min and max
	for (int i = 0; i < sizeof(points)/sizeof(Vector3); i++) {
		min = Vector3Min(min, points[i]);
		max = Vector3Max(max, points[i]);
	}
}

bool RectangleCollider::Overlaps(Vector2 point)
{
	// Check if point is within rectangle
	return !(point.x < min.x || point.y < min.y || point.x > max.x || point.y > max.y);
}


bool RectangleCollider::Overlaps(Collider* other, Vector3 thisVel, Vector3 otherVel, Hit& result)
{
	// If other collider is a rectangle
	if (other->type == cType::Rectangle) {
		RectangleCollider* rec = (RectangleCollider*)other;

		// Check if objects are already colliding
		if (!(max.x < rec->min.x || max.y < rec->min.y || min.x > rec->max.x || min.y > rec->max.y)) {
			return true;
		}

		// Get the relative velocity between the two
		Vector3 relV = Vector3Subtract(thisVel, otherVel);

		float hitTime = 0.0f;
		float outTime = 1.0f;
		Vector2 overlapTime = Vector2Zero();

		// X axis overlap relative going left
		if (relV.x < 0)
		{
			// No overlap
			if (rec->max.x < min.x) { 
				return false; 
			}

			// Calculate the time of overlap
			if (rec->max.x > min.x) { 
				outTime = fminf((min.x - rec->max.x) / relV.x, outTime);
			}
			if (max.x < rec->min.x)
			{
				overlapTime.x = (max.x - rec->min.x) / relV.x;
				hitTime = fmaxf(overlapTime.x, hitTime);
			}
		}
		// X axis overlap relative going right
		else if (relV.x > 0)
		{
			// No overlap
			if (rec->min.x > max.x) { 
				return false; 
			}

			// Calculate the time of overlap
			if (max.x > rec->min.x) {
				outTime = fminf((max.x - rec->min.x) / relV.x, outTime);
			}
			if (rec->max.x < min.x)
			{
				overlapTime.x = (min.x - rec->max.x) / relV.x;
				hitTime = fmaxf(overlapTime.x, hitTime);
			}
		}

		// No overlap
		if (hitTime > outTime) {
			return false;
		}



		// Y axis overlap
		if (relV.y < 0)
		{
			// No overlap
			if (rec->max.y < min.y) { 
				return false; 
			}

			// Calculate the time of overlap
			if (rec->max.y > min.y) {
				outTime = fminf((min.y - rec->max.y) / relV.y, outTime);
			}
			if (max.y < rec->min.y)
			{
				overlapTime.y = (max.y - rec->min.y) / relV.y;
				hitTime = fmaxf(overlapTime.y, hitTime);
			}
		}
		else if (relV.y > 0)
		{
			// No overlap
			if (rec->min.y > max.y) { 
				return false; 
			}

			// Calculate the time of overlap
			if (max.y > rec->min.y) {
				outTime = fminf((max.y - rec->min.y) / relV.y, outTime);
			}
			if (rec->max.y < min.y)
			{
				overlapTime.y = (min.y - rec->max.y) / relV.y;
				hitTime = fmaxf(overlapTime.y, hitTime);
			}
		}

		// No overlap
		if (hitTime > outTime) {
			return false;
		}


		// Scale velocity by normalized hit time
		result.OutVel = Vector3(relV);
		result.OutVel.x *= -hitTime;
		result.OutVel.y *= -hitTime;


		// Hit normal is on axis with the highest overlap time (Taking into account moving direction
		result.HitNormal = Vector2();
		// More overlap on x axis
		if (overlapTime.x > overlapTime.y)
		{
			result.HitNormal = { relV.x >= 0 ? 1.0f : -1.0f, 0 };
		}
		// More overlap in y axis
		else
		{
			result.HitNormal = { 0, relV.y >= 0 ? 1.0f : -1.0f };
		}
		return true;

	}
	// If other collider is a circle
	else if (other->type == cType::Circle) {
		// Cast other object to circle and call its overlap function
		CircleCollider* cir = (CircleCollider*)other;
		cir->Overlaps(this, otherVel, thisVel, result);
	}

}

// Expand this collider by the size of another collider
void RectangleCollider::Inflate(Collider* other)
{
	if (other->type == cType::Rectangle) {
		RectangleCollider* rec = (RectangleCollider*)other;
		Vector3 extents = rec->Extents();

		min.x -= extents.x;
		min.y -= extents.y;

		max.x += extents.x;
		max.y += extents.y;
	}
	if (other->type == cType::Circle) {
		CircleCollider* cir = (CircleCollider*)other;

		min.x -= cir->radius;
		min.y -= cir->radius;
		max.x += cir->radius;
		max.y += cir->radius;
	}

}
	

Vector2 RectangleCollider::ClosestPoint(Vector2 point)
{
	float x = Clamp(point.x, min.x, max.x);
	float y = Clamp(point.y, min.y, max.y);
	return { x, y };
}
