#pragma once
#include "UIObject.h"
class UIText : public UIObject
{
public:
	UIText(float x, float y, std::string strText, int size, int colour);
	virtual ~UIText();

	std::string text = "";
	int fontSize = 16;
	Color fontColour;

	void Draw() override;

	Vector2 GetCentreOffset();
};

