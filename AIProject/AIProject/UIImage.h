#pragma once
#include "UIObject.h"
class UIImage : public UIObject
{
public:
	UIImage(float x, float y, char* imagePath, int colour);
	virtual ~UIImage();
};

