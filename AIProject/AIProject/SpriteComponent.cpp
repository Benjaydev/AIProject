#pragma once
#include "SpriteComponent.h"

// Destructor
SpriteComponent::~SpriteComponent()
{
	// Unload image from memory
	UnloadImage(*image);
	delete image;
	image = nullptr;

	// Unload texture from memory
	UnloadTexture(*texture);
	delete texture;
	texture = nullptr;
}

// Load image from file
void SpriteComponent::Load(char* filename)
{
	// Load image
	*image = LoadImage(filename);
	// Create texture
	*texture = LoadTextureFromImage(*image);

	// Store the original loaded width and height
	defaultWidth = texture->width;
	defaultHeight = texture->height;
}


void SpriteComponent::SetScale(float scale) {
	// Store the scale
	textureScale = scale;

	// Scale width and height by values
	texture->width *= scale;
	texture->height *= scale;
}