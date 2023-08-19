#include "Button.h"

void Button_function::DrawRec(Vector2 origin, Vector2 size, Color color, char* text) {
    Color colorBtn = {51,187,197,255};
    Color colorText = {255,255,255,255};
    Color hoverColorBtn = {51,187,197,204};
    Color hoverColorText = {255,255,255,255};
    Color pressColor = {200,255,224,175};
    Color pressColorText = {150,150,150,255};


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
            DrawText(text, origin.x + 40, origin.y + (size.y-36)/2, 20, hoverColorText);
        }
    }
    else
    {
        DrawRectangle(origin.x,origin.y,size.x,size.y,colorBtn);
        DrawText(text, origin.x + 40, origin.y + (size.y - 36)/2, 20, colorText);
    }
}

void Button_function::DrawRecSearch(Vector2 origin, Vector2 size, Color color, char* text)
{
    Color colorBtn = {245,245,245,255};
    Color colorText = {51,187,197,255};
    Color hoverColorBtn = {133,230,197,255};
    Color hoverColorText = {50,50,50,255};
    Color pressColor = {200,255,224,175};
    Color pressColorText = {150,150,150,255};

    DrawRectangle(origin.x,origin.y,size.x,size.y,colorBtn);
    DrawText(text, origin.x + 40, origin.y + (size.y - 36)/2, 20, colorText);
    DrawRectangleLinesEx(button, 3, {51,187,197,255});

    // if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}))
    // {
    //     if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    //     {
    //         DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
    //         DrawText(text, origin.x + 40, origin.y + (size.y - 36)/2, 20, pressColorText);
    //     }
    //     else
    //     {
    //         DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
    //         DrawText(text, origin.x + 40, origin.y + (size.y-50)/2, 20, hoverColorText);
    //     }
    // }
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

bool Button_function::isPressed(bool outline)
{
    // Vector2 mouse = GetMousePosition();
    // bool pressed = false;
    // if(CheckCollisionPointRec(mouse, this->button))
    // {
    //     if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    //         pressed = true;
    // }
    // else
    //     pressed = false;

    // return pressed;

    Vector2 mousePoint = GetMousePosition();
    bool btnAction = false;
    int btnState = 0;

    // Check button state
    if (CheckCollisionPointRec(mousePoint, button))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;

    if(btnState == 2 && outline)
        DrawRectangleLinesEx(button, 3, BLACK);
    if (btnAction)
        return true;
    
    return false;
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
    base = LoadTexture("assets\\star-button-blank.png");
    faved = LoadTexture("assets\\star-button-on.png");
    if(!data->favourite)
        cur = base;
    else
        cur = faved;
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
    DrawTexturePro(cur, {0, 0, (float)cur.width, (float)cur.height}, {origin.x + size.x - 50, origin.y + 10, 45, 45}, {0, 0}, 0, RAYWHITE);
    DrawText(data->data.c_str(), origin.x + 20, origin.y + 20, 30, colorText);
    DrawText(text, origin.x + 40, origin.y + 60, 25, colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}) && GetMousePosition().y >= 200 && GetMousePosition().y <= 725)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawTexturePro(cur, {0, 0, (float)cur.width, (float)cur.height}, {origin.x + size.x - 50, origin.y + 10, 45, 45}, {0, 0}, 0, RAYWHITE);
            DrawText(data->data.c_str(), origin.x + 20, origin.y + 20, 30, pressColorText);
            DrawText(text, origin.x + 40, origin.y + 60, 25, pressColorText);
        }
        else
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawTexturePro(cur, {0, 0, (float)cur.width, (float)cur.height}, {origin.x + size.x - 50, origin.y + 10, 45, 45}, {0, 0}, 0, RAYWHITE);
            DrawText(data->data.c_str(), origin.x + 20, origin.y + 20, 30, hoverColorText);
            DrawText(text, origin.x + 40, origin.y + 60, 25, hoverColorText);
        }
    }
}

ReturnButton::ReturnButton(Vector2 origin, Vector2 size, Color color)
{
    this->origin = origin; 
    this->size = size;
    this->color = color;
    button = {origin.x, origin.y, size.x, size.y};
    image = LoadTexture("assets\\back-button.png");
}

void ReturnButton::Draw()
{
    DrawTexturePro(image, {0, 0, (float)image.width, (float)image.height}, {origin.x, origin.y, size.x, size.y}, {0, 0}, 0, RAYWHITE);
}

bool ReturnButton::Update()
{
    this->Draw();
    if(this->isPressed(false))
        return true;
    return false;
}

FavButton::FavButton(Vector2 origin, Vector2 size, Word* word)
: state(word->favourite)
{
    this->origin = origin; 
    this->size = size;
    this->color = color;
    button = {origin.x, origin.y, size.x, size.y};
    base = LoadTexture("assets\\star-button-blank.png");
    faved = LoadTexture("assets\\star-button-on.png");
    if(!state)
        cur = base;
    else
        cur = faved;
}

void FavButton::Draw()
{
    DrawTexturePro(cur, {0, 0, (float)cur.width, (float)cur.height}, {origin.x, origin.y, size.x, size.y}, {0, 0}, 0, RAYWHITE);
}

void FavButton::SetTexture(bool isFav)
{
    if(!isFav)
        cur = base;
    else
        cur = faved;        
}

bool FavButton::Update(Word* word)
{
    this->Draw();
    if(this->isPressed(false))
    {
        if(word->favourite)
        {
            word->favourite = false;
            SetTexture(false);
        }
        else
        {
            word->favourite = true;
            SetTexture(true);
        }
    }
    return word->favourite;
}

WordButton::~WordButton()
{}