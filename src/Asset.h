#pragma once

#ifndef ASSET_H
#define ASSET_H

#include "raylib.h"

class Asset
{
public:
    Texture2D base;
    Texture2D faved;
    Texture2D image;
    Font font;

    Asset()
    {
        base = LoadTexture("assets\\star-button-blank.png");
        faved = LoadTexture("assets\\star-button-on.png");
        image = LoadTexture("assets\\back-button.png");
        font = LoadFont("data\\Open_Sans\\static\\OpenSans_Condensed-Bold.ttf");
    }
};

#endif