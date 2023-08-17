#include "Button.h"

void Button_function::DrawRec(Vector2 origin, Vector2 size, Color color, char* text) {
    Color colorBtn = {51,187,197,255};
    Color colorText = {50,50,50,255};
    Color hoverColorBtn = {133,230,197,255};
    Color hoverColorText = {50,50,50,255};
    Color pressColor = {200,255,224,175};
    Color pressColorText = {150,150,150,255};

    DrawRectangle(origin.x,origin.y,size.x,size.y,colorBtn);
    DrawText(text, origin.x + 40, origin.y + (size.y - 36)/2, 20, colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawText(text, origin.x + 40, origin.y + (size.y - 36)/2, 20, pressColorText);
        }
        else
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawText(text, origin.x + 40, origin.y + (size.y - 36)/2, 20, hoverColorText);
        }
    }
}

void modes_buttons::Draw() {
    Color colorBtn = {97,75,195,110};
    Color colorText = {50,50,50,255};
    Color hoverColorBtn = {97,75,195,170};
    Color hoverColorText = {10,10,10,255};
    Color pressColor = {151,187,197,175};
    Color pressColorText = {100,100,100,255};

    for(int i = 0; i < 5; ++i) {
        Rectangle mode;
        mode.x = origin.x + (size.x + 25)*i;
        mode.y = origin.y - 10;
        mode.width = size.x;
        mode.height = size.y;
        mode_buttons.push_back(mode);
    }
    for(int i = 0; i < 5; ++i) {
        DrawRectangle(mode_buttons[i].x, mode_buttons[i].y, mode_buttons[i].width, mode_buttons[i].height, colorBtn);
        DrawText(modes[i].c_str(), mode_buttons[i].x + 40, mode_buttons[i].y + 10, 20, colorText);
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[0])) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangleRec(mode_buttons[0], pressColor);
            DrawText(modes[0].c_str(), mode_buttons[0].x + 40, mode_buttons[0].y + 10, 20, pressColorText);
        }
        else
        {
            DrawRectangleRec(mode_buttons[0], hoverColorBtn);
            DrawText(modes[0].c_str(), mode_buttons[0].x + 40, mode_buttons[0].y + 10, 20, hoverColorText);
        }
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[1])) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangleRec(mode_buttons[1], pressColor);
            DrawText(modes[1].c_str(), mode_buttons[1].x + 40, mode_buttons[1].y + 10, 20, pressColorText);
        }
        else
        {
            DrawRectangleRec(mode_buttons[1], hoverColorBtn);
            DrawText(modes[1].c_str(), mode_buttons[1].x + 40, mode_buttons[1].y + 10, 20, hoverColorText);
        }
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[2])) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangleRec(mode_buttons[2], pressColor);
            DrawText(modes[2].c_str(), mode_buttons[2].x + 40, mode_buttons[2].y + 10, 20, pressColorText);
        }
        else
        {
            DrawRectangleRec(mode_buttons[2], hoverColorBtn);
            DrawText(modes[2].c_str(), mode_buttons[2].x + 40, mode_buttons[2].y + 10, 20, hoverColorText);
        }
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[3])) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangleRec(mode_buttons[3], pressColor);
            DrawText(modes[3].c_str(), mode_buttons[3].x + 40, mode_buttons[3].y + 10, 20, pressColorText);
        }
        else
        {
            DrawRectangleRec(mode_buttons[3], hoverColorBtn);
            DrawText(modes[3].c_str(), mode_buttons[3].x + 40, mode_buttons[3].y + 10, 20, hoverColorText);
        }
    }
    if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[4])) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangleRec(mode_buttons[4], pressColor);
            DrawText(modes[4].c_str(), mode_buttons[4].x + 40, mode_buttons[4].y + 10, 20, pressColorText);
        }
        else
        {
            DrawRectangleRec(mode_buttons[4], hoverColorBtn);
            DrawText(modes[4].c_str(), mode_buttons[4].x + 40, mode_buttons[4].y + 10, 20, hoverColorText);
        }
    }
}

bool& Button_function::isPressed()
{
    Vector2 mouse = GetMousePosition();
    bool pressed = false;
    if(CheckCollisionPointRec(mouse, this->button))
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            pressed = true;
    }
    else
        pressed = false;

    return pressed;
}

WordButton::WordButton(Word* data, Vector2 origin, Vector2 size, Color color)
: data(data), showable()
{
    this->origin = origin;
    this->size = size;
    this->color = color;
    this->createShowable();
}

WordButton::WordButton()
: data(nullptr), showable()
{}

void WordButton::createShowable()
{
    int maxShow = std::min(2, int(data->defs.size())); 
    for (int j = 0; j < maxShow; j++)
    {
        std::string s = data->defs[j]->data;
        if(s.length() * 13 > button.width - 13)
        {
            for (int k = 0; k < 3; k++)
                s.insert(s.begin() + button.width / 13 + k, '.');
            s.insert(s.begin() + button.width / 13 + 3, '\n');
        }
        showable.append(s);
    }

    showable.pop_back();
    int length = showable.length();
    char res[showable.length() + 1];

    for(int i = 0; i < length; ++i)
        res[i] = showable[i];

    res[length] = '\0';
    
    strcpy(text, res);
}

void WordButton::Draw()
{
    Color colorBtn = {51,187,197,255};
    Color colorText = {50,50,50,255};
    Color hoverColorBtn = {133,230,197,255};
    Color hoverColorText = {50,50,50,255};
    Color pressColor = {200,255,224,175};
    Color pressColorText = {150,150,150,255};

    DrawRectangle(origin.x,origin.y,size.x,size.y,colorBtn);
    DrawText(data->data.c_str(), origin.x + 20, origin.y + 20, 30, colorText);
    DrawText(text, origin.x + 40, origin.y + 50, 20, colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawText(data->data.c_str(), origin.x + 20, origin.y + 20, 30, pressColorText);
            DrawText(text, origin.x + 40, origin.y + 50, 20, pressColorText);
        }
        else
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawText(data->data.c_str(), origin.x + 20, origin.y + 20, 30, hoverColorText);
            DrawText(text, origin.x + 40, origin.y + 50, 20, hoverColorText);
        }
    }
}