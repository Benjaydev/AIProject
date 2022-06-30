#pragma once
#include "UIInputBox.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "Pathfinding.h"
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

	NodeGraph nodeGraph;

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

