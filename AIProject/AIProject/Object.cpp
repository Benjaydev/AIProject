#pragma once
#include "raymath.h"
#include "Game.h"
using namespace std;

Object::Object()
{
}

Object::~Object()
{
	// Delete sprite if valid
	if (sprite != nullptr) {
		delete sprite;
		sprite = nullptr;
	}
	
	// Unparent this object
	if(parent != nullptr){
		UnParent();
	}


	// Unparent all children from this object
	for (int i = 0; i < children.size(); i++) {
		children[i]->parent = nullptr;
		children[i]->physics->parentPhysics = nullptr;
	}
	// Clear children vector
	children.clear();
	children.shrink_to_fit();

	// Remove physics component
	delete physics;
	physics = nullptr;

	// Remove from game
	RemoveFromGameWorld();
}

void Object::RemoveFromGameWorld() {
	// Find and remove from game objects vector
	Game::objects.erase(std::remove(Game::objects.begin(), Game::objects.end(), this), Game::objects.end());
}

void Object::DeleteSelf()
{
	// Delete self
	delete this;
}

void Object::AddToGameWorld() {
	// Remove from game if already added
	RemoveFromGameWorld();

	// Add to game
	id = Game::AddObjectToGame(this);

	// Add all children to game world
	for (int i = 0; i < children.size(); i++) {
		// If id is invalid
		if (children[i]->id == 0) {
			children[i]->AddToGameWorld();
		}
		
	}
}

void Object::AddChild(Object* child) {
	// Add self to parent
	child->ParentTo(this);
}

void Object::RemoveChild(Object* child) {
	// Unparent child
	child->UnParent();
}

void Object::DeleteChild(Object* child) {
	// Unparent child
	child->UnParent();

	// Remove from game
	child->RemoveFromGameWorld();

	// Delete child
	delete child;
}


void Object::ParentTo(Object* p) {
	// Set parent
	parent = p;

	// Set parent physics
	physics->parentPhysics = parent->physics;

	// Add to children vector
	parent->children.push_back(this);
	
	// Flag parent to update physics children list
	parent->shouldReinstantiatePhysicsChildren = true;
	parent->UpdateChildPhysics();
}

void Object::UnParent() {
	// Unparent physics
	physics->parentPhysics = nullptr;

	// Contains any children
	if (parent->children.size() > 0) {
		// Find wanted child
		if (std::find(parent->children.begin(), parent->children.end(), this) != parent->children.end()) {
			// Remove child from this object
			parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());
		}
		// Flag parent to update physics children list
		parent->shouldReinstantiatePhysicsChildren = true;
		parent->UpdateChildPhysics();
	}

	// Unparent
	parent = nullptr;
}



void Object::LoadSprite(char* filename) {
	// Create sprite component and load image
	sprite = new SpriteComponent();
	sprite->Load(filename);
	hasSprite = true;
	
}

void Object::CopySpriteByReference(SpriteComponent* s)
{
	// Create new sprite component
	sprite = new SpriteComponent();

	// Copy texture from reference
	*sprite->texture = LoadTextureFromImage(*s->image);
	// Copy size from reference
	sprite->defaultWidth = s->defaultWidth;
	sprite->defaultHeight = s->defaultHeight;

	hasSprite = true;
	usesReferencedSprite = true;
}


void Object::OnUpdate(float DeltaTime)
{
}

void Object::Update(float DeltaTime)
{
	OnUpdate(DeltaTime);
	physics->Update(DeltaTime);

	UpdateChildPhysics();


}
void Object::UpdateChildPhysics() {
	// If the physics needs to update children (Called when the children in this object change)
	if (shouldReinstantiatePhysicsChildren) {
		// Reset children physics list
		physics->childrenPhysics.clear();
		// Re-add all current children physics
		for (int i = 0; i < children.size(); i++) {
			physics->childrenPhysics.push_back(children[i]->physics);
		}
		shouldReinstantiatePhysicsChildren = false;
	}
}


void Object::OnDraw()
{
}

void Object::Draw()
{
	OnDraw();

	if (hasSprite) {
		// Get rotation
		float rotation = (float)atan2(physics->globalTransform.m1, physics->globalTransform.m0);

		// If game should not be closing
		if (!WindowShouldClose()) {
			// Get position of object
			Vector2 position = { physics->globalTransform.m8, physics->globalTransform.m9 };
			// Draw to screen
			DrawTextureEx(*sprite->texture, position, rotation * RAD2DEG, 1, sprite->colour);

		}
	}
	
	/*
	// Debug mode show collider bounds
	if (physics->collider != nullptr && Environment::DebugActive) {
		physics->collider->DrawDebug();
	}*/
	
}
