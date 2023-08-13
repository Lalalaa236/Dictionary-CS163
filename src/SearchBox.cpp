#include "SearchBox.h"

SearchBox::SearchBox(Vector2 origin, Vector2 size, Color color)
: origin(origin), size(size), bufflen(0), state(false), startSearch(false), color(color)
{
    box.x = this->origin.x;
    box.y = this->origin.y;

    box.width = this->size.x;
    box.height = this->size.y;

    buffer[0] = '\0';
}

SearchBox::~SearchBox()
{
    buffer[0] = '\0';
    bufflen = 0;
}

void SearchBox::DrawBox()
{
    DrawRectangle(this->box.x, this->box.y, this->box.width, this->box.height, this->color);
}

bool SearchBox::Pressed()
{
    Vector2 mouse = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if(CheckCollisionPointRec(mouse, this->box))
        {
            this->state = true;
            this->startSearch = false;
            return true;
        }
        else
        {
            this->state = false;
            this->startSearch = false;
            return false;
        }
    }

    return this->state;
}

void SearchBox::HandleInput(char* input, int& length)
{
    if(this->Pressed())
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        if((key >= 32) && (key <= 125) && (length < 31))
        {
            input[length] = (char)key;
            input[length + 1] = '\0'; // Add null terminator at the end of the string.
            length++;
        }

        key = GetCharPressed();  // Check next character in the queue

        if(IsKeyPressed(KEY_BACKSPACE))
        {
            length--;
            if(length < 0) 
                length = 0;
            input[length] = '\0';
        }

        key = GetCharPressed();

        if(IsKeyPressed(KEY_ENTER))
        {
            this->state = false;
            this->startSearch = true;
            return;
        }
        CursorBlink(GetFrameTime());
        std::cout << "input: " << input << "!\n";
    }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}
void SearchBox::CursorBlink(float time) //blinking cursor 
{
    cursorBlinkTime += time;
    if (cursorBlinkTime >= 1.0f)
        cursorBlinkTime = 0.0f;
}
void SearchBox::DrawInput()
{
    DrawText(buffer, this->box.x + 10, this->box.y + (this->box.height - 36)/2, 48, SKYBLUE);
    if(bufflen == 0 && this->state == false)
        DrawText("Search", this->box.x + 10, this->box.y + (this->box.height - 36)/2, 48, LIGHTGRAY);
    if(this->state)
    {
        if (cursorBlinkTime < 0.5f)
            DrawRectangle(this->box.x + 10 + MeasureText(buffer, 48), this->box.y + (this->box.height - 70) / 2, 2, 70, WHITE); //blinking cursor 
        DrawRectangleLinesEx(this->box, 5, DARKBLUE);    }
}