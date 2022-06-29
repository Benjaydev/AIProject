#include "UIText.h"

UIText::UIText(float x, float y, std::string strText, int size, int colour)
{
	// Setup object
	physics->SetPosition(x, y);

	// Store text values
	text = strText;
	fontSize = size;
	fontColour = GetColor(colour);

	AddToGameWorld();
}

UIText::~UIText()
{
}


void UIText::Draw()
{
	DrawText(text.c_str(), physics->globalTransform.m8, physics->globalTransform.m9, fontSize, fontColour);
}

Vector2 UIText::GetCentreOffset()
{
	// Return the half width and height
	return Vector2({ -(float)MeasureText(text.c_str(), fontSize)/2, -((fontSize*(1.0f - (1.0f/3.0f)))/2) });
}
