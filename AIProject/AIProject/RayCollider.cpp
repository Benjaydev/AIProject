#include "Collider.h"

RayCollider::RayCollider() {
	type = cType::Ray;
}

RayCollider::RayCollider(Vector2 start, Vector2 dir, float len) {
	type = cType::Ray;

	origin = start;
	direction = dir;
	length = len;
}

RayCollider::~RayCollider()
{
}

bool RayCollider::Overlaps(Vector2 point)
{
	return false;
}

bool RayCollider::Overlaps(Collider* other, Hit& result)
{
	// If other collider is a rectangle
	if (other->type == cType::Rectangle) {
        // Cast other collider to circle collider
        RectangleCollider* rec = (RectangleCollider*)other;
        // get distances to each axis of the box 
        float xmin, xmax, ymin, ymax;

        // get min and max in the x-axis  
        if (direction.x < 0)
        {
            // (you may need to change the access modifiers of AABB.min/max) 
            xmin = (rec->max.x - origin.x) / direction.x;
            xmax = (rec->min.x - origin.x) / direction.x;
        }
        else
        {
            xmin = (rec->min.x - origin.x) / direction.x;
            xmax = (rec->max.x - origin.x) / direction.x;
        }

        // get min and max in the y-axis 
        if (direction.y < 0)
        {
            ymin = (rec->max.y - origin.y) / direction.y;
            ymax = (rec->min.y - origin.y) / direction.y;
        }
        else
        {
            ymin = (rec->min.y - origin.y) / direction.y;
            ymax = (rec->max.y - origin.y) / direction.y;
        }

        // ensure within box 
        if (xmin > ymax || ymin > xmax)
            return false;

        // the first contact is the largest of the two min 
        float t = fmaxf(xmin, ymin);

        // intersects if within range 
        if (t >= 0 && t <= length)
        {
            result.HitPoint = Vector2Add(origin, direction);
            result.HitPoint.x* t;
            result.HitPoint.y* t;
            return true;
        }
	
	}

	if (other->type == cType::Circle) {
        // Cast other collider to circle collider
        CircleCollider* cir = (CircleCollider*)other;

        // ray origin to sphere center 
            // (you may need to change the access modifier of sphere.center) 
        Vector2 L = Vector2Subtract(cir->center, origin);

        // project sphere center onto ray 
        float t = Vector2DotProduct(L, direction);

        // get sqr distance from sphere center to ray 
        float dd = Vector2DotProduct(L, L) - (t * t);

        // subtract penetration amount from projected distance 
        t -= (float)sqrt((cir->radius * cir->radius) - dd);

        // It intersects if within ray length 
        if (t >= 0 && t <= length)
        {
            result.HitPoint = Vector2Add(origin, direction);
            result.HitPoint.x* t;
            result.HitPoint.y* t;
            return true;
        }

	}

    return false;
}
