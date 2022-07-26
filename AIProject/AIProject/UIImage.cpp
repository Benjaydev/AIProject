#include "UIImage.h"

UIImage::UIImage(float x, float y, char* imagePath, int colour)
{
	physics->SetPosition(x, y);
	// Load image that is one pixel big
	LoadSprite(imagePath);
	// Expand by width and height
	sprite->colour = GetColor(colour);


	AddToGameWorld();

}

UIImage::~UIImage()
{
}