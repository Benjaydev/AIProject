#pragma once
#include "UIInputBox.h"
#include "UIPanel.h"
#include "UIButton.h"

class Game
{
public:
	Game();
	~Game();

	void Start();
	void Update();
	void Draw();


	static std::vector<Object*> objects;

	static int lifetimeObjectCount;
	static int AddObjectToGame(Object* obj) {
		objects.push_back(obj);
		lifetimeObjectCount++;
		// Return count for object id
		return lifetimeObjectCount;
	}

};

