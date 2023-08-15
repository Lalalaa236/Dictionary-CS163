#pragma once

#ifndef BUTTON_H
#define BUTTON_H


#include "raylib.h"
#include <iostream>
#include <stdlib.h>  
#include <vector>
#include "Dictionary.h"
#include "SearchBox.h"
#include <cstring>

using std::string;
using std::vector;


class Button_function
{
public:
    Vector2 origin;
    Vector2 size;
    Rectangle button;
    Color color;
    char text[101];

    void DrawRec(Vector2 origin, Vector2 size, Color color);
    bool Pressed();
    void Drawtext();
    virtual void specific_function() {};
};

class search_by_def_button : public Button_function
{
public:
    search_by_def_button(Vector2 _origin, Vector2 _size, Color _color) : Button_function()
    {
        origin = {50, 200};
        size = {100, 100};
        color = RED;
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "Search by definition");
    }

    void Draw()
    {
        DrawRec(origin, size, color);
    }
};

class search_by_word_button : public Button_function
{
public:
    search_by_word_button(Vector2 _origin, Vector2 _size, Color _color)
    {
        origin = {50, 310};
        size = {100, 100};
        color = RED;
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "Search by word");
    }

    void DrawButton()
    {
        DrawRectangleRec(button, color);
    }
};


#endif