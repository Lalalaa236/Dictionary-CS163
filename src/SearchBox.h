#ifndef SEARHBOX_H
#define SEARCHBOX_H

#include "raylib.h"
#include <string>

using std::string;

class SearchBox
{
public:
    Rectangle box;
    Color color;
    Vector2 origin;
    Vector2 size;
    bool mouseOnText;
    string input;

    SearchBox(Vector2 origin, Vector2 size, Color color);
    void DrawSearchBox();
    void HandleInput();
    void DrawInput();
};

#endif