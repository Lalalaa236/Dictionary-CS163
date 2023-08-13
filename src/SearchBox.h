#ifndef SEARHBOX_H
#define SEARCHBOX_H

#include "raylib.h"
#include <iostream>
#include <string>

using std::string;

class SearchBox
{
public:
    Rectangle box;
    Color color;
    Vector2 origin;
    Vector2 size;

    char buffer[32];
    int bufflen;
    bool state;
    bool startSearch;

    SearchBox(Vector2 origin, Vector2 size, Color color);
    ~SearchBox();
    bool Pressed();
    void DrawBox();
    void HandleInput(char* input, int& length);
    void DrawInput();
    string getInput();
};

#endif