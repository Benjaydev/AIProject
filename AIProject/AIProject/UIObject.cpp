#include "UIObject.h"

UIObject::UIObject()
{
	tag = "UI";

	// UI shouldn't have physics
	physics->LockAxis = { 1, 1 };
	physics->hasPhysicsCheck = false;


	AddToGameWorld();

}
UIObject::~UIObject()
{
}
