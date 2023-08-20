#include "Button.h"

void Button_function::DrawRec(Vector2 origin, Vector2 size, Color color, char* text,Color color_text, int text_size) {
    Color colorBtn = color;
    Color colorText = color_text;
    Color hoverColorBtn = color;
    Color hoverColorText = color_text;
    Color pressColor = color;
    Color pressColorText = color_text;
    Color layerHover = {100,100,100,70};
    Color layerPress = {255,255,255,70};

    DrawRectangle(origin.x,origin.y,size.x,size.y,colorBtn);
    DrawTextEx(asset->font30,text, {origin.x + 25, origin.y + (size.y - 20)/2}, text_size,2, colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawRectangle(origin.x,origin.y,size.x,size.y, layerPress);
            DrawTextEx(asset->font30,text, {origin.x + 25, origin.y + (size.y - 20)/2}, text_size,2, pressColorText);
        }
        else
        {   
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawRectangle(origin.x,origin.y,size.x,size.y, layerHover);
            DrawTextEx(asset->font30,text, {origin.x + 25, origin.y + (size.y - 20)/2}, text_size,2, hoverColorText);
        }
    }
}

void Button_function::DrawTab(Vector2 origin, Vector2 size, Color color, char* title, char* content,Color color_text, int text_size) {
    Color colorBtn = color;
    Color colorText = color_text;
    Color hoverColorBtn = color;
    Color hoverColorText = {50,50,50,255};
    Color pressColor = color;
    Color pressColorText = {50,50,50,255};
    Color layerHover = {255,255,255, 100};
    Color layerPress = {255,255,255, 70};

    DrawRectangle(origin.x,origin.y,size.x,size.y,WHITE);
    Rectangle rec_title = {origin.x+5,origin.y+10,110,35};
    DrawRectangle(rec_title.x,rec_title.y,rec_title.width,rec_title.height,colorBtn);

    DrawTextEx(asset->font30,title,{rec_title.x + 10, rec_title.y + 5}, text_size,2, WHITE);
    DrawTextEx(asset->font30,content,{origin.x + 10, origin.y + (size.y)/2}, text_size-2,2,colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawRectangle(origin.x,origin.y,size.x,size.y, layerPress);
            DrawTextEx(asset->font30,title, {origin.x + 10, origin.y + (size.y - 20)/2}, text_size,2, pressColorText);
        }
        else
        {   
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawRectangle(origin.x,origin.y,size.x,size.y, layerHover);
            DrawTextEx(asset->font30,title, {origin.x + 10, origin.y + (size.y - 20)/2}, text_size,2, hoverColorText);
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
    Rectangle dataset = {origin.x,origin.y,size.x,size.y};
    DrawRectangle(dataset.x,dataset.y,dataset.width,dataset.height,PURPLE);
    DrawTextEx(asset->font30,"Dataset",{origin.x + 20, origin.y + 25}, 25,2, WHITE);
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
                DrawTextEx(asset->font30,modes[i].c_str(),{mode_buttons[i].x + 15,mode_buttons[i].y + 10}, 25,2, colorText);
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

WordButton::WordButton(Asset* asset, Word* _data, Vector2 _origin, Vector2 _size, Color _color)
: data(_data), showable()
{
    this->asset = asset;
    data = _data;
    origin = _origin;
    size = _size;
    color = _color;
    button = {origin.x, origin.y, size.x, size.y};
    text[0] = '\0';
    // base = LoadTexture("assets\\star-button-blank.png");
    // faved = LoadTexture("assets\\star-button-on.png");
    if(!data->favourite)
        cur = asset->base;
    else
        cur = asset->faved;
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
    DrawTextEx(asset->font30, data->data.c_str(), {origin.x + 20, origin.y + 20}, 35, 0, colorText);
    DrawTextEx(asset->font30, text, {origin.x + 40, origin.y + 60}, 25, 0, colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}) && GetMousePosition().y >= 180 && GetMousePosition().y <= 725)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawTexturePro(cur, {0, 0, (float)cur.width, (float)cur.height}, {origin.x + size.x - 50, origin.y + 10, 45, 45}, {0, 0}, 0, RAYWHITE);
            DrawTextEx(asset->font30, data->data.c_str(), {origin.x + 20, origin.y + 20}, 35, 0, pressColorText);
            DrawTextEx(asset->font30, text, {origin.x + 40, origin.y + 60}, 25, 0, pressColorText);
        }
        else
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawTexturePro(cur, {0, 0, (float)cur.width, (float)cur.height}, {origin.x + size.x - 50, origin.y + 10, 45, 45}, {0, 0}, 0, RAYWHITE);
            DrawTextEx(asset->font30, data->data.c_str(), {origin.x + 20, origin.y + 20}, 35, 0, hoverColorText);
            DrawTextEx(asset->font30, text, {origin.x + 40, origin.y + 60}, 25, 0, hoverColorText);
        }
    }
}

ReturnButton::ReturnButton(Asset* asset, Vector2 origin, Vector2 size, Color color)
{
    this->asset = asset;
    this->origin = origin; 
    this->size = size;
    this->color = color;
    button = {origin.x, origin.y, size.x, size.y};
    image = asset->image;
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

FavButton::FavButton(Asset* asset, Vector2 origin, Vector2 size, Word* word)
: state(word->favourite)
{
    this->asset = asset;
    this->origin = origin; 
    this->size = size;
    this->color = color;
    button = {origin.x, origin.y, size.x, size.y};
    // base = LoadTexture("assets\\star-button-blank.png");
    // faved = LoadTexture("assets\\star-button-on.png");
    if(!state)
        cur = asset->base;
    else
        cur = asset->faved;
}

void FavButton::Draw()
{
    DrawTexturePro(cur, {0, 0, (float)cur.width, (float)cur.height}, {origin.x, origin.y, size.x, size.y}, {0, 0}, 0, RAYWHITE);
}

void FavButton::SetTexture(bool isFav)
{
    if(!isFav)
        cur = this->asset->base;
    else
        cur = this->asset->faved;        
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