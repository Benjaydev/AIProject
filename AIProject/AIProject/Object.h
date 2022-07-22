#pragma once
#include "PhysicsComponent.h"
#include <iostream>
#include <vector>
#include "SpriteComponent.h"


class Object
{
public:
	Object();
	virtual ~Object();

	// Flags
	bool shouldReinstantiatePhysicsChildren = false;
	bool isWaitingDestroy = false;
	bool hasSprite = false;
	bool usesReferencedSprite = false;

	bool isOnScreen = true;
	bool hasCheckedForOnScreen = false;


	// Identification
	int id = 0;
	std::string tag = "";
	
	// Sprite object
	SpriteComponent* sprite = nullptr;

	Object* parent = nullptr;
	std::vector<Object*> children;

	PhysicsComponent* physics = new PhysicsComponent();
	
	// World functions
	void AddToGameWorld();
	void RemoveFromGameWorld();
	void DeleteSelf();

	// Children functions
	void DeleteChild(Object* child);
	void AddChild(Object* child);
	void RemoveChild(Object* child);
	void UpdateChildPhysics();

	// Parent functions
	void ParentTo(Object* p);
	void UnParent();

	void SetIsOnScreen(bool state);

	
	virtual void OnUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void OnDraw();
	virtual void Draw();

	// Collisions
	virtual void CollideEvent(Hit hit, Object* other){};

	// Sprites
	void LoadSprite(char* filename);
	void CopySpriteByReference(SpriteComponent* s);
	void CreateSpriteFromTexture(Texture2D texture);


	// Operator overloads for vector operations
	bool operator== (const Object* other) const { return id == other->id; }
	bool operator!= (const Object* other) const { return !operator==(other); }

};

