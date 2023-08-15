#include "Button.h"

void Button_function::DrawRec(Vector2 origin, Vector2 size, Color color, char* text) {
    DrawRectangle(origin.x,origin.y,size.x,size.y,color);
    DrawText(text, origin.x + 40, origin.y + (size.y - 36)/2, 20, LIGHTGRAY);
}

bool Button_function::Pressed() {
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if(CheckCollisionPointRec(GetMousePosition(), this->button)) return true;
        else return false;
    }
}