#include "UIInputBox.h"
#include <algorithm>
#include <string>

UIInputBox::UIInputBox(float x, float y, float width, float height, int buttonColour, int hColour, int fColour, UIText* defText, int mSize, bool intOnly)
{
	defaultText = defText->text;
	currentText = defText->text;
	maxSize = mSize;

	defaultColour = ColorToInt(defText->fontColour);
	hoverColour = hColour;
	focusedColour = fColour;

	// If can only have integers
	isIntOnly = intOnly;

	physics->SetPosition(x, y);

	// Setup sprite
	boxSprite = new UIPanel(0, 0, width, height, buttonColour);
	AddChild(boxSprite);
	Vector2 offset = boxSprite->sprite->GetCentreOffset();
	boxSprite->physics->SetPosition(offset.x, offset.y);

	
	// Add collider sized to sprite
	physics->SetCollider(cType::Rectangle);
	physics->FitColliderWH(boxSprite->sprite->GetWidth(), boxSprite->sprite->GetHeight(), { x,y });

	// Add text to box
	boxText = defText;
	Vector2 textOffset = defText->GetCentreOffset();
	AddChild(boxText);
	defText->physics->SetPosition(textOffset.x, textOffset.y);
	boxText->AddToGameWorld();

	
	AddToGameWorld();
}

// Destructor
UIInputBox::~UIInputBox()
{
	boxSprite->isWaitingDestroy = true;
	boxText->isWaitingDestroy = true;
}

void UIInputBox::Update(float DeltaTime)
{
	boxText->fontColour = GetColor(defaultColour);
	// Set the display text
	boxText->text = currentText;
	// Re-center the text in box
	Vector2 offset = boxText->GetCentreOffset();
	boxText->physics->SetPosition(offset.x, offset.y);


	bool overlaps = physics->collider->Overlaps(GetMousePosition());

	// Hover
	if (overlaps) {
		OnHover();
	}
	// If box has focus
	if (isFocused) {
		boxText->fontColour = GetColor(focusedColour);
	}

	// Button Click
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		if (overlaps) {
			OnClick();
		}
		else {
			isFocused = false;
		}
	}

	
	// If not focused, ignore typing
	if (!isFocused) {
		return;
	}

	// Get all keys that are pressed
	std::string keys = GetKeysPressed();
	if (keys != "") {
		// Remove character
		if (keys == "backspace") {
			// Remove last character
			if (currentText.size() == 1) {
				// Use 0 for empty if type is integer
				currentText = isIntOnly ? "0" : " ";
			}
			// Resize text
			currentText.resize(fmaxf(currentText.size() - 1, 1));
		}
		else {
			// Add keys pressed to text
			currentText = currentText + keys;

			// Restrain character within size
			if (currentText.size() > maxSize) {
				currentText.resize(maxSize);
			}
			if (maxSize == 1) {
				currentText = keys[0];
			}
		}
		
		// If input box uses ints
		if (isIntOnly) {
			// Clamp to max and min
			int num = std::stoi(currentText);
			num = Clamp(num, intMin, intMax);

			currentText = std::to_string(num);
		}
	}	
}

void UIInputBox::OnClick()
{
	isFocused = true;
	boxText->fontColour = GetColor(focusedColour);
}

void UIInputBox::OnHover()
{
	boxText->fontColour = GetColor(hoverColour);
}

std::string UIInputBox::GetKeysPressed()
{
	std::string pressedKeys = "";

	// Integer inputs
	if (IsKeyPressed(KEY_ZERO)) pressedKeys += "0";
	if (IsKeyPressed(KEY_ONE)) pressedKeys += "1";
	if (IsKeyPressed(KEY_TWO)) pressedKeys += "2";
	if (IsKeyPressed(KEY_THREE)) pressedKeys += "3";
	if (IsKeyPressed(KEY_FOUR)) pressedKeys += "4";
	if (IsKeyPressed(KEY_FIVE)) pressedKeys += "5";
	if (IsKeyPressed(KEY_SIX)) pressedKeys += "6";
	if (IsKeyPressed(KEY_SEVEN)) pressedKeys += "7";
	if (IsKeyPressed(KEY_EIGHT)) pressedKeys += "8";
	if (IsKeyPressed(KEY_NINE)) pressedKeys += "9";
	
	// Return backspace to remove charactes
	if (IsKeyPressed(KEY_BACKSPACE)) return "backspace";


	// Don't check for any other inputs if integer only
	if (isIntOnly) {
		return pressedKeys;
	}

	// Alphabetical inputs
	if (IsKeyPressed(KEY_A)) pressedKeys += "a";
	if (IsKeyPressed(KEY_B)) pressedKeys += "b";
	if (IsKeyPressed(KEY_C)) pressedKeys += "c";
	if (IsKeyPressed(KEY_D)) pressedKeys += "d";
	if (IsKeyPressed(KEY_E)) pressedKeys += "e";
	if (IsKeyPressed(KEY_F)) pressedKeys += "f";
	if (IsKeyPressed(KEY_G)) pressedKeys += "g";
	if (IsKeyPressed(KEY_H)) pressedKeys += "h";
	if (IsKeyPressed(KEY_I)) pressedKeys += "i";
	if (IsKeyPressed(KEY_J)) pressedKeys += "j";
	if (IsKeyPressed(KEY_K)) pressedKeys += "k";
	if (IsKeyPressed(KEY_L)) pressedKeys += "l";
	if (IsKeyPressed(KEY_M)) pressedKeys += "m";
	if (IsKeyPressed(KEY_N)) pressedKeys += "n";
	if (IsKeyPressed(KEY_O)) pressedKeys += "o";
	if (IsKeyPressed(KEY_P)) pressedKeys += "p";
	if (IsKeyPressed(KEY_Q)) pressedKeys += "q";
	if (IsKeyPressed(KEY_R)) pressedKeys += "r";
	if (IsKeyPressed(KEY_S)) pressedKeys += "s";
	if (IsKeyPressed(KEY_T)) pressedKeys += "t";
	if (IsKeyPressed(KEY_U)) pressedKeys += "u";
	if (IsKeyPressed(KEY_V)) pressedKeys += "v";
	if (IsKeyPressed(KEY_W)) pressedKeys += "w";
	if (IsKeyPressed(KEY_X)) pressedKeys += "x";
	if (IsKeyPressed(KEY_Y)) pressedKeys += "y";
	if (IsKeyPressed(KEY_Z)) pressedKeys += "z";
	// Space input
	if (IsKeyPressed(KEY_SPACE)) pressedKeys += " ";
	// If holding shift, capitilise inputs
	if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) { std::transform(pressedKeys.begin(), pressedKeys.end(), pressedKeys.begin(), ::toupper); };
	

	return pressedKeys;
}