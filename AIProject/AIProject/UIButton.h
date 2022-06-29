#pragma once
#include "UIObject.h"
#include "UIText.h"
#include "UIPanel.h"
#include <functional>

class UIButton : public UIObject
{
public:
	UIButton(float x, float y, float width, float height, int colour, int hColour, UIText* text);
	virtual ~UIButton();

	std::function<void()> callFunction;

	UIPanel* buttonSprite;
	UIText* buttonText;

	int defaultColour;
	int hoverColour;
	int deactiveColour;
	bool isActive = true;


	void Update(float DeltaTime) override;
	void OnClick();
	void OnHover();
	void AssignCallMethod(std::function<void()> callMethod) { callFunction = callMethod; };
};

