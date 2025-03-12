#include "Background.h"

Background::Background() {}

Background::Background(Texture2D mainTexture, Texture2D upperTexture)
{
    _mainTexture = mainTexture;
    _upperTexture = upperTexture;
    mainTexturePosition = { -2500,-2500 };
    upperTexturePosition = { -2500,-2500 };
    width = _mainTexture.width;
    height = mainTexture.height;
    parallexStrength = 0.05;
    scale = 5;
}

void Background:: draw()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            DrawTextureEx(_mainTexture, { mainTexturePosition.x + j * width * scale,mainTexturePosition.y + i * width * scale }, 0, scale, WHITE);
            DrawTextureEx(_upperTexture, { upperTexturePosition.x + j * width * scale,upperTexturePosition.y + i * width * scale }, 0, scale, WHITE);
        }

    }
}

void Background::  xUpdateMain(float speed)
{
    mainTexturePosition.x += speed;
    upperTexturePosition.x += speed - (speed * parallexStrength);
}

void Background:: yUpdateMain(float speed)
{
    mainTexturePosition.y += speed;
    upperTexturePosition.y += speed - (speed * parallexStrength);
}

void Background:: check_bound()
{
    if (mainTexturePosition.x <= -7000)
    {
        mainTexturePosition.x = -7000;
        upperTexturePosition.x = -7000;
    }

    if (mainTexturePosition.x < 0 - GetScreenWidth() / 2)
        mainTexturePosition.x = 0 - GetScreenWidth() / 2;
}

void Background:: xUpdateUpper(float speed)
{
    upperTexturePosition.x += speed;
}
   
void Background:: yUpdateUpper(float speed)
{
    upperTexturePosition.y += speed;
}

Background::~Background()
{
}
