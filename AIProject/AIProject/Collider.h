#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include "Hit.h"
// ALL COLLIDERS ARE FOUND IN THIS HEADER

// Collider type
enum class cType { None, Rectangle, Circle };

// Child colliders will override the majority of functionality of the base collider class
class Collider
{
public:
	Collider();
	~Collider();

	Collider* Copy(Collider* copy);

	cType type = cType::None;

	// Overlap functions
	virtual bool Overlaps(Collider* other, Vector3 thisVel, Vector3 otherVel, Hit& result) { return false;  };
	virtual bool Overlaps(Vector2 point) { return false; };
	bool OverlapsScreen(Vector3 velocity, Hit& result);;

	virtual void DrawDebug() {};

	virtual bool IsEmpty() { return false; };

	// Fit colliders
	virtual void Fit(Vector3 points[]) {};
	virtual void Fit(std::vector<Vector3> points) {};

	virtual void Inflate(Collider* other) {};

	virtual void Translate(float x, float y) {};

	virtual Vector2 ClosestPoint(Vector2 point) { return { 0,0 }; }

};

// CIRCLE COLLIDER
class RectangleCollider : public Collider
{
public:
	RectangleCollider();
	RectangleCollider(Vector3 otherMin, Vector3 otherMax);
	RectangleCollider(RectangleCollider* copy);
	~RectangleCollider();


	Vector3& min = boundries[0];
	Vector3& max = boundries[1];

	// Get the corners of the rectangle
	std::vector<Vector3> GetCorners() {
		std::vector<Vector3> corners;
		corners.push_back(min);
		corners.push_back({ min.x, max.y, min.z });
		corners.push_back(max);
		corners.push_back({ max.x, min.y, min.z });
		return corners;
	}

	Vector3 Center();
	Vector3 Extents() { return { abs(max.x - min.x) * 0.5f, abs(max.y - min.y) * 0.5f, abs(max.z - min.z) * 0.5f }; }

	void DrawDebug() override;

	bool IsEmpty();
	void Empty();

	void Fit(std::vector<Vector3> points);
	void Fit(Vector3 points[]);

	// Override overlap functions
	bool Overlaps(Vector2 point) override;
	bool Overlaps(Collider* other, Vector3 thisVel, Vector3 otherVel, Hit& result) override;

	void Inflate(Collider* other) override;

	Vector2 ClosestPoint(Vector2 point) override;

	void Translate(float x, float y) override;

protected:
	Vector3 boundries[2] = { { -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity() }, { std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() } };

};


// CIRCLE COLLIDER
class CircleCollider : public Collider
{
public:
	CircleCollider();
	CircleCollider(Vector2 point, float r);
	CircleCollider(CircleCollider* copy);
	~CircleCollider();

	Vector2 center;
	float radius;

	void DrawDebug() override;

	void Fit(std::vector<Vector3> points);
	void Fit(Vector3 points[]);

	// Override overlap functions
	bool Overlaps(Vector2 point) override;
	bool Overlaps(Collider* other, Vector3 thisVel, Vector3 otherVel, Hit& result) override;

	void Translate(float x, float y) override;

};
