#include "SearchBox.h"
SearchBox::SearchBox(Asset* asset, Vector2 origin, Vector2 size, Color color)
: asset(asset), origin(origin), size(size), bufflen(0), input(), state(false), startSearch(false), color(color)
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
    if(this->startSearch)
        this->startSearch = false;
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
            this->input = buffer;
        }
        CursorBlink(GetFrameTime());
        // std::cout << "input: " << input << "!\n";
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
    Color colorBtnLine = {51,187,197,255};
    DrawTextEx(asset->font50, buffer, {this->box.x + 40, this->box.y + (this->box.height - 45)/2}, 48, 0, colorBtnLine);
    if(bufflen == 0 && this->state == false)
        //DrawText("Search", this->box.x + 40, this->box.y + (this->box.height - 45)/2, 48, {155,155,155,255});
        DrawTextEx(asset->font50, "Search", {this->box.x + 40, this->box.y + (this->box.height - 45)/2}, 48, 0, {155,155,155,255});
    if(this->state)
    {
        if (cursorBlinkTime < 0.5f)
            DrawTextEx(asset->font50, "|", {this->box.x + 40 + MeasureTextEx(asset->font50, buffer, 48, 0).x, this->box.y + (this->box.height - 50) / 2}, 48, 0, {155,155,155,255});
            //DrawRectangle(this->box.x + 40 + MeasureTextEx(asset->font, buffer, 48, 0).x, this->box.y + (this->box.height - 50) / 2, 2, 50, GRAY); //blinking cursor 
    }
}