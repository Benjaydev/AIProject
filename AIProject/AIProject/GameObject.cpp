#include "GameObject.h"

Texture2D GameObject::chefCostume;
Texture2D GameObject::janitorCostume;
Texture2D GameObject::securityCostume;
Texture2D GameObject::pistolTexture;
bool GameObject::areCostumesLoaded = false;
bool GameObject::areWeaponsLoaded = false;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	if (areCostumesLoaded) {
		UnloadTexture(chefCostume);
		UnloadTexture(janitorCostume);
		UnloadTexture(securityCostume);
	}
}

void GameObject::InitSprites()
{
	AddChild(spriteObject);
	if (spriteObject->sprite != nullptr) {
		spriteObject->physics->SetRotation(-90 * DEG2RAD);
		spriteObject->physics->SetPosition(-spriteObject->sprite->GetCentreOffset().x, spriteObject->sprite->GetCentreOffset().y);
	}


	AddChild(costumeSprite);
	if (costumeSprite->sprite != nullptr) {
		costumeSprite->physics->SetRotation(-90 * DEG2RAD);
		costumeSprite->physics->SetPosition(-costumeSprite->sprite->GetCentreOffset().x, costumeSprite->sprite->GetCentreOffset().y);
	}

	
	AddChild(weaponSprite);
	if (weaponSprite->sprite != nullptr) {
		weaponSprite->physics->SetRotation(-90 * DEG2RAD);
		weaponSprite->physics->SetPosition(weaponSprite->sprite->GetWidth()+10, 0);
	}
	
}

void GameObject::SetCostume(std::string costumeName)
{
	if (!areCostumesLoaded) {
		chefCostume = LoadTexture((char*)"Images/ChefCostume.png");
		janitorCostume = LoadTexture((char*)"Images/JanitorCostume.png");
		securityCostume = LoadTexture((char*)"Images/SecurityCostume.png");
		areCostumesLoaded = true;
	}

	costume = costumeName;

	Texture2D selectedCostume;
	if (costume == "Chef") {
		selectedCostume = chefCostume;
	}
	else if (costume == "Janitor") {
		selectedCostume = janitorCostume;
	}
	else if (costume == "Security") {
		selectedCostume = securityCostume;
	}
	else {
		costumeSprite->hasSprite = false;
		return;
	}


	costumeSprite->CreateSpriteFromTexture(selectedCostume);

	costumeSprite->sprite->SetScale(0.5f);
	costumeSprite->sprite->defaultWidth = selectedCostume.width;
	costumeSprite->sprite->defaultHeight = selectedCostume.height;

	InitSprites();
}

bool GameObject::hasSuspiciousWeapon()
{


	return weapon == "Pistol";
}

void GameObject::SetWeapon(std::string weaponName) {
	if (!areWeaponsLoaded) {
		pistolTexture = LoadTexture((char*)"Images/Pistol.png");
		areWeaponsLoaded = true;
	}

	weapon = weaponName;

	Texture2D selectedTexture;
	if (weaponName == "Pistol") {
		selectedTexture = pistolTexture;
	}
	else {
		weaponSprite->hasSprite = false;
		return;
	}

	weaponSprite->CreateSpriteFromTexture(selectedTexture);
	
	weaponSprite->sprite->SetScale(0.75f);
	weaponSprite->sprite->defaultWidth = selectedTexture.width;
	weaponSprite->sprite->defaultHeight = selectedTexture.height;

	InitSprites();
}
