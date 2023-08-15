#include "Button.h"

void Button_function::DrawRec(Vector2 origin, Vector2 size, Color color) {
    DrawRectangle(this->button.x, this->button.y, this->button.width, this->button.height, this->color);
}

bool Button_function::Pressed() {
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if(CheckCollisionPointRec(GetMousePosition(), this->button)) return true;
        else return false;
    }
}

void Button_function::Drawtext() {
    DrawText(this->text, this->button.x + 10, this->button.y + (this->button.height - 36)/2, 48, LIGHTGRAY);
}

