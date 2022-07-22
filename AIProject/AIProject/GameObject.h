#pragma once
#include "Object.h"
class GameObject : public Object
{
public:
	GameObject();
	virtual ~GameObject();

	std::string weapon;
	std::string costume;


	Object* spriteObject = new Object();
	Object* costumeSprite = new Object();
	Object* weaponSprite = new Object();



	static bool areCostumesLoaded;
	static bool areWeaponsLoaded;
	static Texture2D chefCostume;
	static Texture2D janitorCostume;
	static Texture2D securityCostume;


	static Texture2D pistolTexture;


	bool hasSuspiciousWeapon();

	void InitSprites();
	void SetCostume(std::string costumeName);

	void SetWeapon(std::string weaponName);



};

