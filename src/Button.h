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
    Asset* asset;
    Vector2 origin;
    Vector2 size;
    Rectangle button;
    Color color;
    Color color_text;
    char title[256];
    char content[256];
    int text_size;
    char text[256];
    bool state = false;

    void DrawRec(Vector2 origin, Vector2 size, Color color, char* text,Color color_text,int text_size);
    void DrawTab(Vector2 origin, Vector2 size, Color color, char* title, char* content,Color color_text, int text_size);
    virtual void specific_function() {};
    bool isPressed(bool outline);

    Button_function() = default;
    Button_function(Asset* asset)
    : asset(asset)
    {}
};

class search_by_def_button : public Button_function
{
public:
    search_by_def_button(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, Color _color_text, int _text_size) 
    : Button_function()
    {
        this->asset = asset;
        origin = _origin; 
        size = _size;    
        color = _color;
        color_text = _color_text;
        text_size = _text_size;    
     
        button = {origin.x, origin.y, size.x, size.y};   
        strcpy(text, "Definition");
    }
    
    void Draw()
    {
        DrawRec(origin, size, color, text,color_text,text_size);
    }
};

class search_by_word_button : public Button_function
{
public:
    search_by_word_button(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, Color _color_text, int _text_size) 
    : Button_function()
    {
        this->asset = asset;
        origin = _origin; 
        size = _size;    
        color = _color;   
        color_text = _color_text;
        text_size= _text_size;
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "Word");
    }

    void Draw()
    {
        DrawRec(origin, size, color, text,color_text,text_size);
    }

};

class add_word_button : public Button_function
{
public:
    add_word_button(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, char* _title, char* _content, Color _color_text, int _text_size) 
    : Button_function()
    {
        this->asset = asset;
        origin = _origin; 
        size = _size;    
        color = _color;   
        color_text = _color_text;
        text_size = _text_size;      
        strcpy(title, _title);
        strcpy(content, _content);    
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "  Games");
    }
    
    void Draw()
    {
        DrawTab(origin, size, color, title,content,color_text,text_size);
    }
};

class history_button : public Button_function
{
public:
    history_button(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, char* _title, char* _content, Color _color_text, int _text_size) 
    : Button_function()
    {
        this->asset = asset;
        origin = _origin; 
        size = _size;    
        color = _color;   
        color_text = _color_text;
        text_size = _text_size;       
        strcpy(title, _title);
        strcpy(content, _content);
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "  History");
    }
    void Draw()
    {
        DrawTab(origin, size, color, title,content,color_text,text_size);
    }
};

class favorite_button : public Button_function
{
public:
    favorite_button(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, char* _title, char* _content, Color _color_text, int _text_size) 
    : Button_function()
    {
        this->asset = asset;
        origin = _origin; 
        size = _size;    
        color = _color;   
        color_text = _color_text;
        text_size = _text_size;  
        strcpy(title, _title);
        strcpy(content, _content);      
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, " Favorite");
    }

    void Draw()
    {
        DrawTab(origin, size, color, title,content,color_text,text_size);
    }
};

class games_button : public Button_function
{
public:
    games_button(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, char* _title, char* _content, Color _color_text, int _text_size) 
    : Button_function()
    {
        this->asset = asset;
        origin = _origin; 
        size = _size;    
        color = _color;   
        color_text = _color_text;
        text_size = _text_size;      
        strcpy(title, _title);
        strcpy(content, _content);    
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "  Games");
    }
    
    void Draw()
    {
        DrawTab(origin, size, color, title,content,color_text,text_size);
    }
};

class reset_button : public Button_function
{
public:
    reset_button(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, Color _color_text, int _text_size) 
    : Button_function()
    {
        this->asset = asset;
        origin = _origin; 
        size = _size;    
        color = _color;   
        color_text = _color_text;
        text_size = _text_size;        
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, "  Reset");
    }
    
    void Draw()
    {
        DrawRec(origin, size, color, text,color_text,text_size);
    }
};

class modes_buttons
{
public:
    vector<string> modes = {"Eng-Eng", "Eng-Vie", "Vie-Eng", "Slang", "Emoji"};
    vector<Rectangle> mode_buttons;

    Vector2 origin;
    Vector2 size;
    Color color;
    Color color_text;
    char text[101];
    int text_size;
    bool isDropdownVisible = false;
    Asset* asset;
    modes_buttons(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, Color _color_text, int _text_size) 
    {
        this->asset = asset;
        origin = _origin;
        size = _size;
        color = _color;
        color_text = _color_text;
        text_size = _text_size;
    }

    void Draw();
};

class WordButton : public Button_function
{
public:
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
public:
    ReturnButton(Asset* asset, Vector2 origin, Vector2 size, Color color);
    void Draw();
    bool Update();
};

class FavButton : public Button_function
{
    // Texture2D base;
    // Texture2D faved;
    Texture2D cur;
    bool state;
public:
    FavButton(Asset* asset, Vector2 origin, Vector2 size, Word* word);

    void Draw();
    void SetTexture(bool isFav);
    bool Update(Word* word);
};
class AddWordScreen : public Button_function
{
    int text_size;
    bool isDropdownVisible = false;
    Texture2D cur;
public:
    bool is_enter_word = false;
    bool is_enter_def = false;
    bool is_enter_type = false;

    string input;
    string input_def;
    string input_type;

    bool startAdd = false;
    char buffer[32];
    char buffer_def[257];
    char buffer_type[32];

    int bufflen;
    int bufflen_def;
    int bufflen_type;

    Asset* asset;
    AddWordScreen(Asset*asset):
    bufflen(0),is_enter_word(false),bufflen_def(0),bufflen_type(0)
    {
        this->asset = asset;
        buffer[0] = '\0';
        buffer_def[0] = '\0';
        buffer_type[0]= '\0';


    }
    float cursorBlinkTime = 0.0f;
    void CursorBlink(float time);
    void Draw(char *input, int& length, char* input_def, int& length_def, char *input_type, int&length_type);
};

class YesNo_button : public Button_function
{
public:
    YesNo_button(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, Color _color_text,string t, int _text_size) 
    : Button_function()
    {
        this->asset = asset;
        origin = _origin; 
        size = _size;    
        color = _color;   
        color_text = _color_text;
        text_size = _text_size;        
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, t.c_str());
    }
    
    void Draw()
    {
        DrawRec(origin, size, color, text,color_text,text_size);
    }
};

class remove_button : public Button_function
{
public:
    remove_button(Asset* asset, Vector2 _origin, Vector2 _size, Color _color, Color _color_text,string t, int _text_size) 
    : Button_function()
    {
        this->asset = asset;
        origin = _origin; 
        size = _size;    
        color = _color;   
        color_text = _color_text;
        text_size = _text_size;        
        button = {origin.x, origin.y, size.x, size.y};
        strcpy(text, t.c_str());
    }
    
    void Draw()
    {
        DrawRec(origin, size, color, text,color_text,text_size);
    }
};

class EditDefButton : public Button_function
{
public: 
    Rectangle displayDef;
    string showable;
    Definition* def;
    Color rectangleColor;
    EditDefButton(Asset* asset, Definition* def, Vector2 pos, Color color);
    void createShowable();
    void Draw(Vector2 pos);
};
#endif