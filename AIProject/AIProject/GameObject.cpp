#include "GameObject.h"
#include "Bullet.h"


Texture2D GameObject::chefCostume;
Texture2D GameObject::janitorCostume;
Texture2D GameObject::securityCostume;
Texture2D GameObject::targetCostume;
Texture2D GameObject::pistolTexture;
Texture2D GameObject::knifeTexture;
bool GameObject::areCostumesLoaded = false;
bool GameObject::areWeaponsLoaded = false;

GameObject::GameObject()
{
	std::string characterPaths[4] = { "Images/CharacterM1.png", "Images/CharacterM2.png", "Images/CharacterW1.png", "Images/CharacterW2.png" };

	spriteObject->LoadSprite((char*)(characterPaths[rand() % 3]).c_str());
	spriteObject->sprite->Scale(0.5f);


	bloodSprite->LoadSprite((char*)"Images/Blood.png");
	AddChild(bloodSprite);
	bloodSprite->AddToGameWorld(true);
	bloodSprite->sprite->Scale(0.1);
	bloodSprite->physics->SetRotation(-90 * DEG2RAD);
	bloodSprite->physics->SetPosition(-bloodSprite->sprite->GetCentreOffset().x, bloodSprite->sprite->GetCentreOffset().y);
	bloodSprite->hasSprite = false;

	physics->SetRotation((rand() % 360) * DEG2RAD);
}

GameObject::~GameObject()
{
	if (areCostumesLoaded) {
		UnloadTexture(chefCostume);
		UnloadTexture(janitorCostume);
		UnloadTexture(securityCostume);
	}
	if (areWeaponsLoaded) {
		UnloadTexture(pistolTexture);
		UnloadTexture(knifeTexture);
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
		targetCostume = LoadTexture((char*)"Images/TargetCostume.png");
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
	else if (costume == "Target") {
		selectedCostume = targetCostume;
	}
	else {
		costumeSprite->hasSprite = false;
		return;
	}


	costumeSprite->CreateSpriteFromTexture(selectedCostume);

	costumeSprite->sprite->Scale(0.5f);
	costumeSprite->sprite->defaultWidth = selectedCostume.width;
	costumeSprite->sprite->defaultHeight = selectedCostume.height;

	InitSprites();
}

bool GameObject::hasSuspiciousWeapon()
{
	return weapon == "Pistol" || weapon == "Knife";
}

void GameObject::SetWeapon(std::string weaponName) {
	if (!areWeaponsLoaded) {
		pistolTexture = LoadTexture((char*)"Images/Pistol.png");
		knifeTexture = LoadTexture((char*)"Images/Knife.png");
		areWeaponsLoaded = true;
	}

	weapon = weaponName;

	Texture2D selectedTexture;
	if (weaponName == "Pistol") {
		selectedTexture = pistolTexture;
	}
	else if (weaponName == "Knife") {
		selectedTexture = knifeTexture;
	}
	else {
		weaponSprite->hasSprite = false;
		return;
	}

	weaponSprite->CreateSpriteFromTexture(selectedTexture);
	
	weaponSprite->sprite->Scale(0.75f);
	weaponSprite->sprite->defaultWidth = selectedTexture.width;
	weaponSprite->sprite->defaultHeight = selectedTexture.height;

	InitSprites();
}

void GameObject::UseWeapon()
{
	if (weapon == "Pistol") {
		new Bullet(physics->GetPosition(), physics->GetFacingDirection());
	}
	else if (weapon == "Knife") {
		hasResetWeapon = false;
		resetWeaponCooldown = 0.1;

		weaponSprite->physics->SetRotation(0);
		weaponSprite->physics->SetPosition(0, -20);


	}
}

void GameObject::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	// Reset weapon position and rotation 
	if (!hasResetWeapon) {
		resetWeaponCooldown -= DeltaTime;
		if (resetWeaponCooldown <= 0) {
			hasResetWeapon = true;
			weaponSprite->physics->SetRotation(-90 * DEG2RAD);
			weaponSprite->physics->SetPosition(weaponSprite->sprite->GetWidth() + 10, 0);
		}
	}


	if (!isAlive) {
		// Spread blood over time
		if (bloodSprite->sprite->GetScale() < 0.75f) {
			bloodSprite->sprite->Scale(fminf(0.75f,bloodSprite->sprite->GetScale() + (DeltaTime / 5)));
			bloodSprite->physics->SetPosition(-bloodSprite->sprite->GetCentreOffset().x, bloodSprite->sprite->GetCentreOffset().y);
		}
	}
}



void GameObject::Kill()
{
	isAlive = false;
	bloodSprite->hasSprite = true;
}
