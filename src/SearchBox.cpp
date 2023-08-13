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
             if (length > 0)
            {
                Dictionary dictionary;
              //  searchResults = dictionary.searchWord(input);
              test.clear();
              for (int i=1;i<=11;i++)
                test.push_back(std::to_string(i));

            }
            return;
        }
        CursorBlink(GetFrameTime());
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
        DrawRectangleLinesEx(this->box, 5, DARKBLUE);    
    }
  if (startSearch)
    {
        float item_height = 50.0f; 
        float dropDownY = box.y + box.height; 
        float total_height = item_height * test.size();
        int max_item = 10;
        int startIndex = static_cast<int>(scroll / item_height);
        int endIndex = startIndex + max_item;
        // scroll
        int wheelMove = -GetMouseWheelMove(); // Reverse the sign of wheelMove
        scroll += wheelMove * item_height;
        // valid range
        float max_scorll = total_height - box.height;
        if (scroll < 0.0f)
            scroll = 0.0f;
        else if (scroll > max_scorll)
            scroll = max_scorll;
        if (endIndex > test.size())
        {
            endIndex = test.size();
            startIndex = endIndex - max_item;
            if (startIndex < 0)
                startIndex = 0;
        }
        DrawRectangle(box.x, dropDownY, box.width, box.height, WHITE); //background
        for (int i = startIndex; i < endIndex && i < test.size(); i++)
        {
            float itemY = dropDownY + item_height * (i - startIndex);
            // Draw the item
            DrawRectangle(box.x, itemY, box.width, item_height, WHITE);
            DrawText(test[i].c_str(), box.x + 10, itemY + 5, 20, BLACK);
            DrawRectangleLines(box.x, itemY, box.width, item_height, WHITE);
        }
    }
}