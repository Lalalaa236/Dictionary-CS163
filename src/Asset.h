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
    Texture2D image1;
    Texture2D saveimage;
    Font font30;
    Font font50;

    Asset()
    {
        base = LoadTexture("assets\\star-button-blank.png");
        faved = LoadTexture("assets\\star-button-on.png");
        image = LoadTexture("assets\\back-button.png");
        image1 = LoadTexture("assets\\edit-button.png");
        saveimage = LoadTexture("assets\\save-button.png");
        font30 = LoadFontEx("assets\\Poppins-Medium.ttf", 30, 0, 0);
        font50 = LoadFontEx("assets\\Poppins-Medium.ttf", 50, 0, 0);
        SetTextureFilter(font30.texture, TEXTURE_FILTER_BILINEAR);
        SetTextureFilter(font50.texture, TEXTURE_FILTER_BILINEAR);
    }
};

#endif