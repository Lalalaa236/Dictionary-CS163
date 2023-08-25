#pragma once

#ifndef SEARHBOX_H
#define SEARCHBOX_H

#include "raylib.h"
#include <iostream>
#include <string>
#include "Dictionary.h"
#include "Asset.h"
using std::string;

class SearchBox
{
private:
    float cursorBlinkTime = 0.0f;
    //std::vector<std::string> test;
    float scroll;
public:
    Rectangle box;
    Color color;
    Vector2 origin;
    Vector2 size;
    string input;

    char buffer[21];
    int bufflen;
    bool state;
    bool startSearch;
    vector<Word*> searchResults;
    Asset* asset;
    SearchBox(Asset* asset, Vector2 origin, Vector2 size, Color color);
    ~SearchBox();
    bool Pressed();
    void DrawBox();
    void HandleInput(char* input, int& length);
    void CursorBlink(float deltaTime);
    void DrawInput();
};

#endif