#pragma once
#include "raylib.h"
class SpriteComponent {
public:
    SpriteComponent() {}
    ~SpriteComponent();

    Texture2D* texture = new Texture2D();
    Image* image = new Image();

    Color colour = WHITE;

    Vector2 tiling = { 1,1 };
    bool shouldTile = false;
    float tiledSpriteRotation = 0;


    float GetWidth() { return (float)texture->width; }
    float GetHeight() { return (float)texture->height; }
    float defaultWidth = 0;
    float defaultHeight = 0;

    void Load(char* filename);

    void Scale(float scale);
    float GetScale() { return textureScale; }

    Vector2 GetCentreOffset() { return { -(texture->width / 2.0f), -(texture->height / 2.0f) }; }

private:
    float textureScale = 1.0f;
};

