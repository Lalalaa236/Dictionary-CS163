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

    Asset()
    {
        base = LoadTexture("assets\\star-button-blank.png");
        faved = LoadTexture("assets\\star-button-on.png");
        image = LoadTexture("assets\\back-button.png");
    }
};

#endif