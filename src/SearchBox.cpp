#include "SearchBox.h"

SearchBox::SearchBox(Vector2 origin, Vector2 size, Color color)
: origin(origin), size(size), mouseOnText(false), color(color)
{
    box.x = this->origin.x;
    box.y = this->origin.y;

    box.width = this->size.x;
    box.height = this->size.y;
}

void SearchBox::DrawSearchBox()
{
    DrawRectangle(this->box.x, this->box.y, this->box.width, this->box.height, this->color);
}

void SearchBox::HandleInput()
{
    int key = GetKeyPressed();
    int length = 0;
    char input[32];

    SetMouseCursor(MOUSE_CURSOR_IBEAM);
    while (key > 0 && CheckCollisionPointRec(GetMousePosition(), this->box))
    {
        if ((key >= 32) && (key <= 125) && (length < 31))
        {
            input[length] = (char)key;
            input[length + 1] = '\0'; // Add null terminator at the end of the string.
            ++length;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if(IsKeyPressed(KEY_BACKSPACE))
    {
        --length;
        if(length < 0) 
            length = 0;
        input[length] = '\0';
    }
    
    
}