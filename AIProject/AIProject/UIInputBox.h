#pragma once
#include "UIObject.h"
#include "UIText.h"
#include "UIPanel.h"
#include <functional>

class UIInputBox : public UIObject
{
public:
	UIInputBox(float x, float y, float width, float height, int buttonColour, int hColour, int fColour, UIText* defText, int mSize, bool intOnly = false);
	virtual ~UIInputBox();

	UIPanel* boxSprite;
	UIText* boxText;

	int defaultColour;
	int hoverColour;
	int focusedColour;


	bool isFocused = false;
	bool isIntOnly = false;
	int intMax = 9;
	int intMin = 1;

	int maxSize = 3;
	std::string defaultText = "0";
	std::string currentText = "0";


	void Update(float DeltaTime) override;
	void OnClick();
	void OnHover();
	std::string GetKeysPressed();


};

