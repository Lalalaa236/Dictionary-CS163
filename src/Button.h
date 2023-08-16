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
#include <cmath>

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

    void DrawRec(Vector2 origin, Vector2 size, Color color, char* text);
    virtual void specific_function() {};
    bool isPressed();

    Button_function() = default;
};

class search_by_def_button : public Button_function
{
public:
    search_by_def_button(Vector2 _origin, Vector2 _size, Color _color) : Button_function()
    {
        origin = _origin; 
        size = _size;    
        color = _color;
        button = {origin.x, origin.y, size.x, size.y};   
        strcpy(text, "Search by \n definition");
    }
    
    void Draw()
    {
        DrawRec(origin, size, color, text);
    }
};

class search_by_word_button : public Button_function
{
public:
    search_by_word_button(Vector2 _origin, Vector2 _size, Color _color) : Button_function()
    {
        origin = _origin; 
        size = _size;    
        color = _color;   
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "Search by \n   word");
    }

    void Draw()
    {
        DrawRec(origin, size, color, text);
    }
};

class history_button : public Button_function
{
public:
    history_button(Vector2 _origin, Vector2 _size, Color _color) : Button_function()
    {
        origin = _origin; 
        size = _size;    
        color = _color;   
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "  History");
    }
    
    void Draw()
    {
        DrawRec(origin, size, color, text);
    }
};

class favorite_button : public Button_function
{
public:
    favorite_button(Vector2 _origin, Vector2 _size, Color _color) : Button_function()
    {
        origin = _origin; 
        size = _size;    
        color = _color;   
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, " Favorite");
    }
    
    void Draw()
    {
        DrawRec(origin, size, color, text);
    }
};

class games_button : public Button_function
{
public:
    games_button(Vector2 _origin, Vector2 _size, Color _color) : Button_function()
    {
        origin = _origin; 
        size = _size;    
        color = _color;   
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "  Games");
    }
    
    void Draw()
    {
        DrawRec(origin, size, color, text);
    }
};

class reset_button : public Button_function
{
public:
    reset_button(Vector2 _origin, Vector2 _size, Color _color) : Button_function()
    {
        origin = _origin; 
        size = _size;    
        color = _color;   
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "  Reset");
    }
    
    void Draw()
    {
        DrawRec(origin, size, color, text);
    }
};

class modes_buttons
{
public:
    vector<string> modes = {"  Eng-Eng", "   Eng-Vie", "   Vie-Eng", "    Slang", "    Emoji"};
    vector<Rectangle> mode_buttons;

    Vector2 origin;
    Vector2 size;
    Color color;
    char text[101];

    modes_buttons(Vector2 _origin, Vector2 _size, Color _color) {
        origin = _origin;
        size = _size;
        color = _color;
    }

    void Draw();
};

class WordButton : public Button_function
{
public:
    Word* data;
    string showable;

    WordButton();
    WordButton(Word* data, Vector2 origin, Vector2 size, Color color);
    

    void createShowable();

    void Draw();
};

#endif