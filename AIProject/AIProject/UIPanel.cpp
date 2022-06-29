#pragma once
#include "UIPanel.h"

UIPanel::UIPanel(float x, float y, float width, float height, int colour)
{
	physics->SetPosition(x, y);
	// Load image that is one pixel big
	LoadSprite((char*)"Images/WhitePixel.png");
	// Expand by width and height
	sprite->texture->width = width;
	sprite->texture->height = height;
	sprite->colour = GetColor(colour);


	AddToGameWorld();

}

UIPanel::~UIPanel()
{
}