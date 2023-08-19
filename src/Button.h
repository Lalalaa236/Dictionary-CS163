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
#include "Asset.h"

using std::string;
using std::vector;


class Button_function
{
public:
    Vector2 origin;
    Vector2 size;
    Rectangle button;
    Color color;
    char text[256];
    bool state = false;

    void DrawRec(Vector2 origin, Vector2 size, Color color, char* text);
    void DrawRecSearch(Vector2 origin, Vector2 size, Color color, char* text);

    virtual void specific_function() {};
    bool isPressed(bool outline); //if you want the outline

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

    void DrawSearch()
    {
        DrawRecSearch(origin, size, color, text);
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

        void DrawSearch()
    {
        DrawRecSearch(origin, size, color, text);
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
    Asset* asset;
    Word* data;
    string showable;
    Texture2D cur;
    // Texture2D base;
    // Texture2D faved;

    WordButton();
    WordButton(Asset* asset, Word* data, Vector2 origin, Vector2 size, Color color);
    ~WordButton();
    

    void createShowable();

    void Draw(Vector2 origin);
    //bool Update();
};

class ReturnButton : public Button_function
{
    Texture2D image;
    Asset* asset;
public:
    ReturnButton(Asset* asset, Vector2 origin, Vector2 size, Color color);
    void Draw();
    bool Update();
};

class FavButton : public Button_function
{
    // Texture2D base;
    // Texture2D faved;
    Asset* asset;
    Texture2D cur;
    bool state;
public:
    FavButton(Asset* asset, Vector2 origin, Vector2 size, Word* word);

    void Draw();
    void SetTexture(bool isFav);
    bool Update(Word* word);
};

#endif