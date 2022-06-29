#include "UIButton.h"

UIButton::UIButton(float x, float y, float width, float height, int colour, int hColour, UIText* text)
{
	tag = "Button";
	physics->SetPosition(x, y);
	
	// Setup button sprite
	buttonSprite = new UIPanel(x, y, width, height, colour);
	defaultColour = colour;
	hoverColour = hColour;
	Color d = GetColor(defaultColour);
	d.a = 100;
	deactiveColour = ColorToInt(d);

	AddChild(buttonSprite);


	// Offset the sprite to the center of the object
	Vector2 offset = buttonSprite->sprite->GetCentreOffset();
	buttonSprite->physics->SetPosition(offset.x, offset.y);

	// Add collider sized to sprite
	physics->SetCollider(cType::Rectangle);
	physics->FitColliderWH(buttonSprite->sprite->GetWidth(), buttonSprite->sprite->GetHeight(), {x,y});
	
	// Add text to button
	buttonText = text;
	Vector2 textOffset = text->GetCentreOffset();
	AddChild(buttonText);
	text->physics->SetPosition(textOffset.x, textOffset.y);
	buttonText->AddToGameWorld();

	AddToGameWorld();
}

UIButton::~UIButton()
{
	// Destroy all
	buttonSprite->isWaitingDestroy = true;
	buttonText->isWaitingDestroy = true;

}

void UIButton::Update(float DeltaTime) {

	// Re-center the text on the button
	Vector2 offset = buttonText->GetCentreOffset();
	buttonText->physics->SetPosition(offset.x, offset.y);

	// If button is not active
	if (!isActive) {
		buttonSprite->sprite->colour = GetColor(deactiveColour);
		return;
	}

	// Set button to its default colour
	buttonSprite->sprite->colour = GetColor(defaultColour);

	// If mouse overlaps the button
	if (physics->collider->Overlaps(GetMousePosition())) {
		// Trigger hover
		OnHover();

		// Button Click
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			OnClick();
		}
	}
	
}

void UIButton::OnHover()
{
	buttonSprite->sprite->colour = GetColor(hoverColour);
}

void UIButton::OnClick()
{
	// Call the assigned function
	if (callFunction != nullptr) {
		callFunction();
	}
	
}


