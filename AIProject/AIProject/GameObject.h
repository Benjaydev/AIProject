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

	Object* bloodSprite = new Object();



	static bool areCostumesLoaded;
	static bool areWeaponsLoaded;
	static Texture2D chefCostume;
	static Texture2D janitorCostume;
	static Texture2D securityCostume;
	static Texture2D targetCostume;


	static Texture2D pistolTexture;
	static Texture2D knifeTexture;

	float resetWeaponCooldown = 0;
	bool hasResetWeapon = true;


	bool isAlive = true;

	bool hasSuspiciousWeapon();

	void InitSprites();
	void SetCostume(std::string costumeName);

	void SetWeapon(std::string weaponName);

	void Update(float DeltaTime) override;

	virtual void UseWeapon();


	virtual void Kill();
};

