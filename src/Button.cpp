#include "Button.h"

void Button_function::DrawRec(Vector2 origin, Vector2 size, Color color, char* text,Color color_text, int text_size) {
    Font font = LoadFont("data\\Open_Sans\\static\\OpenSans_Condensed-Bold.ttf");
    Color colorBtn = color;
    Color colorText = color_text;
    Color hoverColorBtn = {133,230,197,255};
    Color hoverColorText = {50,50,50,255};
    Color pressColor = {200,255,224,175};
    Color pressColorText = {150,150,150,255};

    DrawRectangle(origin.x,origin.y,size.x,size.y,colorBtn);
    DrawTextEx(font,text, {origin.x + 25, origin.y + (size.y - 36)/2}, text_size,2, colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawTextEx(font,text, {origin.x + 25, origin.y + (size.y - 36)/2}, text_size,2, pressColorText);
        }
        else
        {   
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawTextEx(font,text, {origin.x + 25, origin.y + (size.y - 36)/2}, text_size,2, hoverColorText);
        }
    }
}
void Button_function::DrawTab(Vector2 origin, Vector2 size, Color color, char* title, char* content,Color color_text, int text_size) {
    Font font = LoadFont("data\\Open_Sans\\static\\OpenSans_Condensed-Bold.ttf");
    Color colorBtn = color;
    Color colorText = color_text;
    Color hoverColorBtn = {133,230,197,255};
    Color hoverColorText = {50,50,50,255};
    Color pressColor = {200,255,224,175};
    Color pressColorText = {150,150,150,255};

    DrawRectangle(origin.x,origin.y,size.x,size.y,WHITE);
    Rectangle rec_title = {origin.x+5,origin.y+10,110,35};
    DrawRectangle(rec_title.x,rec_title.y,rec_title.width,rec_title.height,colorBtn);

    DrawTextEx(font,title,{rec_title.x + 10, rec_title.y + 5}, text_size,2, WHITE);
     DrawTextEx(font,content,{origin.x + 10, origin.y + (size.y - 36)/2}, text_size-2,2,colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawTextEx(font,title, {origin.x + 10, origin.y + (size.y - 36)/2}, text_size,2, pressColorText);
        }
        else
        {   
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawTextEx(font,title, {origin.x + 10, origin.y + (size.y - 36)/2}, text_size,2, hoverColorText);
        }
    }
}
void modes_buttons::Draw() 
{
    Color colorBtn = color;
    Color colorText = color_text;
    Color hoverColorBtn = {97,75,195,170};
    Color hoverColorText = {10,10,10,255};
    Color pressColor = {151,187,197,175};
    Color pressColorText = {100,100,100,255};
    Font font = LoadFont("data\\Open_Sans\\static\\OpenSans_Condensed-Bold.ttf");
    Rectangle dataset = {origin.x,origin.y,size.x,size.y};
    DrawRectangle(dataset.x,dataset.y,dataset.width,dataset.height,PURPLE);
    DrawTextEx(font,"Dataset",{origin.x + 10, origin.y + 25}, 25,2, WHITE);
    for(int i = 0; i < 5; ++i) {
        Rectangle mode;
        mode.x = origin.x;
        mode.y = origin.y + size.y*(i+1);
        mode.width = size.x;
        mode.height = size.y;
        mode_buttons.push_back(mode);
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if(CheckCollisionPointRec(GetMousePosition(), dataset)&&!isDropdownVisible) 
        {
                isDropdownVisible = true; 
        }
        else {
                isDropdownVisible = false; 
        }
    }
    if (isDropdownVisible) 
    {
            for (int i = 0; i < 5; ++i) {
                DrawRectangle(mode_buttons[i].x, mode_buttons[i].y, mode_buttons[i].width, mode_buttons[i].height, colorBtn);
                DrawTextEx(font,modes[0].c_str(),{mode_buttons[i].x + 5,mode_buttons[i].y + 10}, 25,2, colorText);
            }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[0])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRec(mode_buttons[0], pressColor);
            }
            else
            {
                DrawRectangleRec(mode_buttons[0], hoverColorBtn);
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[1])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRec(mode_buttons[1], pressColor);
            }
            else
            {
                DrawRectangleRec(mode_buttons[1], hoverColorBtn);
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[2])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRec(mode_buttons[2], pressColor);
            }
            else
            {
                DrawRectangleRec(mode_buttons[2], hoverColorBtn);
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[3])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRec(mode_buttons[3], pressColor);
            }
            else
            {
                DrawRectangleRec(mode_buttons[3], hoverColorBtn);
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[4])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRec(mode_buttons[4], pressColor);
            }
            else
            {
                DrawRectangleRec(mode_buttons[4], hoverColorBtn);
            }
        }
    }
}
bool Button_function::isPressed()
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

WordButton::WordButton(Word* _data, Vector2 _origin, Vector2 _size, Color _color)
: data(_data), showable()
{
    data = _data;
    origin = _origin;
    size = _size;
    color = _color;
    button = {origin.x, origin.y, size.x, size.y};
    text[0] = '\0';
    createShowable();
}

WordButton::WordButton()
: data(nullptr), showable()
{}

void WordButton::createShowable()
{
    int maxShow = std::min(2, int(data->defs.size()));// show max 2 defs
    for (int j = 0; j < maxShow; j++)
    {
        std::string s = data->defs[j]->data;
        int textWidth = MeasureText(s.c_str(), 25);
        if(textWidth > (button.width - 20))
        {
            s = s.substr(0, 45);
            // cout << s << "\n";
            for (int k = 0; k < 3; ++k)
                s.append(".");
        }
        s.append("\n");
        showable.append(s);
    }

    int length = showable.length();
    
    char res[length];
    

    for(int i = 0; i < length - 1; ++i)
        res[i] = showable[i];

    res[length - 1] = '\0';
    
    for(int i = 0; i < length; ++i)
        text[i] = res[i];


}

void WordButton::Draw(Vector2 origin)
{
    Color colorBtn = {51,187,197,255};
    Color colorText = {50,50,50,255};
    Color hoverColorBtn = {133,230,197,255};
    Color hoverColorText = {50,50,50,255};
    Color pressColor = {200,255,224,175};
    Color pressColorText = {150,150,150,255};

    DrawRectangle(origin.x,origin.y,size.x,size.y,colorBtn);
    DrawText(data->data.c_str(), origin.x + 20, origin.y + 20, 30, colorText);
    DrawText(text, origin.x + 40, origin.y + 60, 25, colorText);
    
    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}) && GetMousePosition().y >= 200 && GetMousePosition().y <= 725)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawText(data->data.c_str(), origin.x + 20, origin.y + 20, 30, pressColorText);
            DrawText(text, origin.x + 40, origin.y + 60, 25, pressColorText);
        }
        else
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawText(data->data.c_str(), origin.x + 20, origin.y + 20, 30, hoverColorText);
            DrawText(text, origin.x + 40, origin.y + 60, 25, hoverColorText);
        }
    }
}