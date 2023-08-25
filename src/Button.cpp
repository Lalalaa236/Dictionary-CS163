#include "Button.h"
#include "App.h"
void Button_function::DrawRec(Vector2 origin, Vector2 size, Color color, char* text,Color color_text, int text_size) {
    Color colorBtn = color;
    Color colorText = color_text;
    Color hoverColorBtn = color;
    Color hoverColorText = color_text;
    Color pressColor = color;
    Color pressColorText = color_text;
    Color layerHover = {200,200,200, 100};
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
    Rectangle rec_title = {origin.x+5,origin.y+10,130,35};
    DrawRectangle(rec_title.x,rec_title.y,rec_title.width,rec_title.height,colorBtn);

    DrawTextEx(asset->font30,title,{rec_title.x + 10, rec_title.y + 5}, text_size,2, WHITE);
    DrawTextEx(asset->font30,content,{origin.x + 10, origin.y + (size.y)/2}, text_size-4,2,colorText);

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

void modes_buttons::Draw(string& fileDir,Dictionary*& dict)
{
    Color colorBtn = {255,98,137,105};
    Color colorText = color_text;
    Color hoverColorBtn = {255,98,137,155};
    Color hoverColorText = {200,200,200,255};
    Color pressColor = {255,98,137,175};
    Color pressColorText = {200,200,200,255};
    Rectangle dataset = {origin.x,origin.y,size.x,size.y};
    DrawRectangle(dataset.x,dataset.y,dataset.width,dataset.height,{255,98,137,255});
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
        if(CheckCollisionPointRec(GetMousePosition(), dataset)&&!isDropdown) 
        {
                isDropdown = true; 
                after_change = false;
        }
    }
    if (isDropdown) 
    {
            for (int i = 0; i < 5; ++i) {
                DrawRectangle(mode_buttons[i].x, mode_buttons[i].y, mode_buttons[i].width, mode_buttons[i].height, colorBtn);
                DrawTextEx(asset->font30,modes[i].c_str(),{mode_buttons[i].x + 15,mode_buttons[i].y + 10}, 25,2, colorText);
            }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[0])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                fileDir = link_data[0];
                DrawRectangleRec(mode_buttons[0], pressColor);
                dict->deleteDict();
                dict->loadData(fileDir);
                change_data = true;

            }
            else
            {
                DrawRectangleRec(mode_buttons[0], hoverColorBtn);
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[1])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                fileDir = link_data[1];
                DrawRectangleRec(mode_buttons[1], pressColor);
                dict->deleteDict();
                dict->loadData(fileDir);
                change_data = true;

            }
            else
            {
                DrawRectangleRec(mode_buttons[1], hoverColorBtn);
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[2])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                fileDir = link_data[2];
                DrawRectangleRec(mode_buttons[2], pressColor);
                dict->deleteDict();
                dict->loadData(fileDir);
                change_data = true;

            }
            else
            {
                DrawRectangleRec(mode_buttons[2], hoverColorBtn);
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[3])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                fileDir = link_data[3];
                DrawRectangleRec(mode_buttons[3], pressColor);
                dict->deleteDict();
                dict->loadData(fileDir);
                change_data = true;

            }
            else
            {
                DrawRectangleRec(mode_buttons[3], hoverColorBtn);
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(), mode_buttons[4])) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                fileDir = link_data[4];
                DrawRectangleRec(mode_buttons[4], pressColor);
                dict->deleteDict();
                dict->loadData(fileDir);
                change_data = true;
            }
            else
            {
                DrawRectangleRec(mode_buttons[4], hoverColorBtn);
            }
        }
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if(CheckCollisionPointRec(GetMousePosition(), dataset)&&!isDropdown) 
        {
                isDropdown = true; 
                after_change = false;
        }
        else if (!CheckCollisionPointRec(GetMousePosition(), dataset)) {
                if (after_change) after_change = false;
                else if (isDropdown) after_change = true;
                isDropdown=false; 
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

void WordButton::Draw(Vector2 origin,bool isHL)
{
    Color colorBtn = WHITE;
    Color colorText = {255,8,74,255};
    Color hoverColorBtn = {255,98,137,30};
    Color hoverColorText = {255,98,137,255};
    Color pressColor = {255,98,137,50};
    Color pressColorText = {255,98,137,255};

    DrawRectangle(origin.x,origin.y,size.x,size.y,colorBtn);
    DrawTexturePro(cur, {0, 0, (float)cur.width, (float)cur.height}, {origin.x + size.x - 50, origin.y + 10, 45, 45}, {0, 0}, 0, RAYWHITE);
    DrawTextEx(asset->font30, data->data.c_str(), {origin.x + 20, origin.y + 20}, 35, 0, colorText);
    DrawTextEx(asset->font30, text, {origin.x + 40, origin.y + 60}, 25, 0, colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}) && GetMousePosition().y >= 180 && GetMousePosition().y <= 725 && !isHL)
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

ShuffleButton::ShuffleButton(Asset* asset, Vector2 origin, Vector2 size, Color color)
{
    this->asset = asset;
    this->origin = origin; 
    this->size = size;
    this->color = color;
    button = {origin.x, origin.y, size.x, size.y};
    image = asset->shuffle;
}

void ShuffleButton::Draw()
{
    DrawRec({origin.x + 7, origin.y}, size, color, "", color, 0);
    DrawTexturePro(image, {0, 0, (float)image.width, (float)image.height}, {origin.x + 10, origin.y + 10, size.x - 20, size.y - 20}, {-6, 0}, 0, RAYWHITE);
}

bool ShuffleButton::Update()
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
void AddWordScreen::CursorBlink(float time) //blinking cursor 
{
    cursorBlinkTime += time;
    if (cursorBlinkTime >= 1.0f)
        cursorBlinkTime = 0.0f;
}
void AddWordScreen::Draw(char *input, int& length, char* input_def, int& length_def, char *input_type, int&length_type)
{
    Rectangle word_rec = {50,90,500,70};
    Vector2 origin = {50,150};
    Rectangle def_rec = {30,origin.y+70,1100,400};
    Rectangle type_rec = {origin.x+500+10,origin.y-50,300,70};
    DrawRectangle(30,50,1100,650,WHITE);
    DrawLine(origin.x,origin.y,500,origin.y,BLACK);
    DrawTextEx(asset->font50, buffer,{origin.x,origin.y-60}, 45, 0,BLACK);
    DrawTextEx(asset->font50, buffer_def,{origin.x,origin.y+70}, 38, 0,BLACK);
    DrawTextEx(asset->font50,buffer_type,{origin.x+500+20,origin.y-50}, 45, 0,BLACK);
    if(bufflen == 0 && is_enter_word == false)
      {
            DrawTextEx(asset->font50, "Enter a word",{origin.x,origin.y-60}, 45, 0,  BLACK);
      }
    if(bufflen_def == 0 && is_enter_def == false)
        DrawTextEx(asset->font50, "Add the definition here",{origin.x,origin.y+70}, 38,2,  {155,155,155,255});
    if(bufflen_type == 0 && is_enter_type == false)
        DrawTextEx(asset->font50, "(Type of the word)",{origin.x+500+10,origin.y-50}, 45,2,  {155,155,155,255});
    if(is_enter_word)
    {
        if (cursorBlinkTime < 0.5f)
            DrawTextEx(asset->font50, "|", {origin.x + MeasureTextEx(asset->font50, buffer, 45, 0).x, origin.y-60}, 45, 0,BLACK);
    }
    if(is_enter_def)
    {
        if (cursorBlinkTime < 0.5f)
            DrawTextEx(asset->font50, "|", {origin.x + MeasureTextEx(asset->font50, buffer_def, 38, 0).x, origin.y+70}, 38, 0,BLACK);
    }
    if(is_enter_type)
    {
        if (cursorBlinkTime < 0.5f)
            DrawTextEx(asset->font50, "|", {origin.x + 500 +20 + MeasureTextEx(asset->font50, buffer_type, 45, 0).x, origin.y-50}, 38, 0,BLACK);
    }  
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(GetMousePosition(), word_rec))
        {
            is_enter_word = true;
            is_enter_def = false;
            is_enter_type  =false;

        }   
        else if (is_enter_word)
            is_enter_word = false;
        else if (CheckCollisionPointRec(GetMousePosition(), def_rec))
        {
            is_enter_def = true;  
            is_enter_word = false;
            is_enter_type  =false;

        }
        else if (is_enter_def)
            is_enter_def = false;  
        else if (CheckCollisionPointRec(GetMousePosition(), type_rec))
        {
            is_enter_type = true;  
            is_enter_word = false;
            is_enter_def = false;
        }
        else if (is_enter_type)
            is_enter_type = false; 

     }
    if (is_enter_word)
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
        this->input = buffer;
        if(IsKeyPressed(KEY_ENTER))
        {
            is_enter_word = false;
        }
        CursorBlink(GetFrameTime());
    }
    else if (!is_enter_def&&!is_enter_type)
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    if (is_enter_def)
    {
     SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        if((key >= 32) && (key <= 125) && (length_def < 256))
        {
            input_def[length_def] = (char)key;
            input_def[length_def + 1] = '\0'; // Add null terminator at the end of the string.
            length_def++;
        }

        key = GetCharPressed();  // Check next character in the queue

        if(IsKeyPressed(KEY_BACKSPACE))
        {
            length_def--;
            if(length_def < 0) 
                length_def = 0;
            input_def[length_def] = '\0';
        }

        key = GetCharPressed();
        this->input_def = buffer_def;
        if(IsKeyPressed(KEY_ENTER))
        {
            is_enter_def = false;
        }
        CursorBlink(GetFrameTime());
    }
    else if (!is_enter_word && !is_enter_type)
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    if (is_enter_type)
    {
     SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        if((key >= 32) && (key <= 125) && (length_type < 31))
        {
            input_type[length_type] = (char)key;
            input_type[length_type + 1] = '\0'; // Add null terminator at the end of the string.
            length_type++;
        }

        key = GetCharPressed();  // Check next character in the queue

        if(IsKeyPressed(KEY_BACKSPACE))
        {
            length_type--;
            if(length_type < 0) 
                length_type = 0;
            input_type[length_type] = '\0';
        }

        key = GetCharPressed();
        this->input_type = buffer_type;
        if(IsKeyPressed(KEY_ENTER))
        {
            is_enter_type = false;
        }
        CursorBlink(GetFrameTime());


    
    }
    else if (!is_enter_word && !is_enter_def)
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);


}
void AddWordScreen::Save(Dictionary*&dict, string& fileDir)
{
    startAdd = false;
    Rectangle save_btn = {30,720,120,40};
    Rectangle cancel_btn = {save_btn.x+120+15,save_btn.y,save_btn.width,save_btn.height};
    DrawRectangle(save_btn.x,save_btn.y,save_btn.width,save_btn.height,PURPLE);
    DrawTextEx(asset->font30,"Save",{save_btn.x+20,720+5}, 30,2, WHITE);
    DrawRectangle(save_btn.x+120+15,save_btn.y,save_btn.width,save_btn.height,WHITE);
    DrawTextEx(asset->font30,"Cancel",{save_btn.x+120+35,720+5}, 30,2, BLACK);
    if(CheckCollisionPointRec(GetMousePosition(),save_btn))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(save_btn.x,save_btn.y,save_btn.width,save_btn.height, {97,75,195,170});
            DrawTextEx(asset->font30,"Save",{30+20,720+5}, 30,2, WHITE);
            if (buffer[0]!='\0'&&buffer_def[0]!='\0'&&buffer_type[0]!='\0')
            {
                vector<string> current;
                current.push_back(input);
                current.push_back("("+input_type+") "+input_def);
                cout<<current[0]<<"\n"<<current[1]<<"\n";
                bool insert = false;
                Word* word;
                insert = true;
                if(!dict->trie.findWhole(current[0], word))
                {
                    word = new Word(current[0]);
                    insert = true;
                    if(!dict->trie.insert(current[0], word))
                    {
                            cout << "Cannot insert: " << current[0] << "\n";
                            delete word;
                            word = nullptr;
                    }
                }
                Definition* def = new Definition(current[1]);
                def->word = word;
                word->defs.push_back(def);
                        cout << "Inserted successfully!\n";
                int index = dict->words.size();
                if(insert)
                    dict->words.push_back(word);
                word->index = index;
                dict->allDef.push_back(def);
                dict->addDefWord(def, current[1]);
                std::ofstream file (fileDir+"data.txt",std::ios::app);
                file<<"\n"<<current[0]<<" "<<current[1];
                file.close();
                startAdd = true;
            }
        }
    else
        {
           DrawRectangle(save_btn.x,save_btn.y,save_btn.width,save_btn.height, {97,75,195,170});
           DrawTextEx(asset->font30,"Save",{30+20,720+5}, 30,2, WHITE);
        }        
    }
    if(CheckCollisionPointRec(GetMousePosition(),cancel_btn))
    {
         if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(save_btn.x+120+15,cancel_btn.y,cancel_btn.width,cancel_btn.height, {136, 143, 153,255});
            DrawTextEx(asset->font30,"Cancel",{save_btn.x+120+35,720+5}, 30,2, BLACK);
            startAdd = true;
        }
    else
        {
           DrawRectangle(save_btn.x+120+15,save_btn.y,save_btn.width,save_btn.height, {136, 143, 153,255});
           DrawTextEx(asset->font30,"Cancel",{save_btn.x+120+35,720+5}, 30,2, BLACK);
        }        
    }

}

WordButton::~WordButton()
{}

void Button_function::DrawChoiceRec(Vector2 origin, Vector2 size, Color color, char* text,Color color_text, int text_size) {
    Color colorBtn = color;
    Color colorText = color_text;
    Color hoverColorBtn = color;
    Color hoverColorText = color_text;
    Color pressColor = color;
    Color pressColorText = color_text;
    Color layerHover = {200,200,200, 100};
    Color layerPress = {255,255,255,70};

    DrawRectangle(origin.x,origin.y,size.x,size.y,colorBtn);
    DrawTextEx(asset->font30,text, {origin.x + 25, origin.y + (size.y - 80)/2}, text_size,1, colorText);

    if(CheckCollisionPointRec(GetMousePosition(), {origin.x, origin.y, size.x, size.y}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawRectangle(origin.x,origin.y,size.x,size.y, pressColor);
            DrawRectangle(origin.x,origin.y,size.x,size.y, layerPress);
            DrawTextEx(asset->font30,text, {origin.x + 25, origin.y + (size.y - 80)/2}, text_size,1, pressColorText);
        }
        else
        {   
            DrawRectangle(origin.x,origin.y,size.x,size.y,hoverColorBtn);
            DrawRectangle(origin.x,origin.y,size.x,size.y, layerHover);
            DrawTextEx(asset->font30,text, {origin.x + 25, origin.y + (size.y - 80)/2}, text_size,1, hoverColorText);
        }
    }
}