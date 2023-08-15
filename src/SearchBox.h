#pragma once

#ifndef SEARHBOX_H
#define SEARCHBOX_H

#include "raylib.h"
#include <iostream>
#include <string>
#include "Dictionary.h"
using std::string;

class SearchBox
{
private:
    float cursorBlinkTime = 0.0f;
    std::vector<std::string> test;
    float scroll;
public:
    Rectangle box;
    Color color;
    Vector2 origin;
    Vector2 size;

    char buffer[32];
    int bufflen;
    bool state;
    bool startSearch;
    vector<Word*> searchResults;
    SearchBox(Vector2 origin, Vector2 size, Color color);
    ~SearchBox();
    bool Pressed();
    void DrawBox();
    void HandleInput(char* input, int& length);
    void CursorBlink(float deltaTime);
    void DrawInput();
    string getInput();
};

#endif