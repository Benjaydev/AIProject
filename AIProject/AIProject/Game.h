#pragma once
#include"Wall.h"
#include "Player.h"
#include "Pathfinding.h"
#include "MapWood.h"

using namespace Pathfinding;

class Game
{
public:
	Game();
	~Game();

	void Start();
	void Update();
	void Draw();

	float DeltaTime;

	void ResetGameObjects();

	

	NodeGraph* nodeGraph;

	Player* player;


	
	MapWood* map1;
	Map* currentMap;


	RectangleCollider* screenRec = new RectangleCollider();

	static std::vector<Vector2> importantLocations;

	static Vector2 screenCenterOffset() {
		return { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	}
	static Vector4 WorldBorders;
	static std::vector<Object*> objects;
	static bool DebugActive;
	static int lifetimeObjectCount;
	static int AddObjectToGame(Object* obj) {
		objects.push_back(obj);
		lifetimeObjectCount++;
		// Return count for object id
		return lifetimeObjectCount;
	}

};

