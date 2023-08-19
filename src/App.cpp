// app.cpp
#include "App.h"

State::State()
: mode(1), dataset(0)
{}

ViewWord::ViewWord(WordButton* word, Screen* screen, App* app)
: word(word), screen(screen), app(app), showable(), origin({150, 180})
{
    SetShowable();
    backButton = new ReturnButton({1050, 112}, {45, 45}, RAYWHITE);
    favButton = new FavButton({1050, 652}, {45, 45}, word->data);
}

ViewWord::~ViewWord()
{
    delete backButton;
    delete favButton;
}

void ViewWord::Render(App* app, Screen* screen)
{
    DrawRectangleRec({100, 650, 1000, 50}, WHITE);
    DrawRectangle(100, 100, 1000, 70, DARKBLUE);

    DrawRectangleLinesEx({100, 100, 1000, 600}, 5, BLACK);
    
    DrawLineEx({100, 650}, {1100, 650}, 5, BLACK);
    
    DrawText(word->data->data.c_str(), 120, 120, 45, BLACK);
    Update();
}

void ViewWord::Update()
{
    BeginScissorMode(150, 170, 1000, 480);
    DrawText(showable.c_str(), this->origin.x, this->origin.y, 30, BLACK);
    float offset = GetMouseWheelMove() * 30;
    if(MeasureTextEx(GetFontDefault(), showable.c_str(), 30, 0).y > 480)
    {
        if(this->origin.y + offset >= 180 && offset > 0)
            this->origin.y = 180;
        else if(this->origin.y + offset <= (700 - MeasureTextEx(GetFontDefault(), showable.c_str(), 30, 0).y) && offset < 0)
            this->origin.y = 700 - MeasureTextEx(GetFontDefault(), showable.c_str(), 30, 0).y;
        else
            this->origin.y += offset;
    }
    // cout << this->origin.y << "\n";
    EndScissorMode();
    if(backButton->Update())
        this->screen->mode = this->screen->Mode::SEARCH;

    if(word->data->favourite)
    {
        if(!favButton->Update(word->data))
        {
            this->app->dict->removeFromFavList(word->data);
            word->cur = word->faved;
        }
    }
    else
    {
        if(favButton->Update(word->data))
        {
            this->app->dict->addToFavList(word->data);
            word->cur = word->faved;
        }
    }
}

void ViewWord::SetShowable()
{
    int size = word->data->defs.size();
    for(int i = 0; i < size; ++i)
    {
        string cpy = word->data->defs[i]->data;
        int count = 0;
        int length = cpy.length();
        for(int j = 0; j < length; ++j)
        {
            if(count == 50)
            {
                int k = findNearestSpace(cpy, length, j);
                cpy[k] = '\n';
                count = 0;
            }
            ++count;
        }
        showable.append(cpy);
        showable.append("\n\n");
    }
    int length = showable.length();
    // cout << showable;
}

int ViewWord::findNearestSpace(const string& s, int length, int pos)
{
    int i = pos;
    for(; i >= 0; --i)
        if(s[i] == ' ')
            break;
    
    int j = pos;
    for(; j < length; ++j)
        if(s[j] == ' ')
            break;
    if(s[i] != ' ')
        return j;
    if(s[j] != ' ')
        return i;

    return (pos - i) > (j - pos) ? j : i;
}

// Word* ViewWord::getWord()
// {
//     return word;
// }
void SearchWord::Render(App* app)
{
    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(viewScreen)
        {
            delete viewScreen;
            viewScreen = nullptr;
        }
        if(word)
            word = nullptr;
        searchbox->DrawBox();
        searchbox->HandleInput(searchbox->buffer, searchbox->bufflen);
        searchbox->DrawInput();
        modesButtons->Draw();

        defButton->Draw();
        wordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        if(historyButton->isPressed(true)) {
            app->setNextScreen(new HistoryScreen);
        }

        if(favoriteButton->isPressed(true)) {
            app->setNextScreen(new FavoriteScreen);
        }

        if(resetButton->isPressed(true)) {
            app->setNextScreen(new ResetWarning);
        }

        if(!searchbox->state)
        {
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                // delete word;
                word = nullptr;
                list = new WordList(app->dict->searchWord(searchbox->input));
                mode = Mode::SEARCH;
            }
            if(mode == Mode::SEARCH && !searchbox->startSearch && list)
            {
                list->Draw();
                word = list->getWord();
                if(word)
                    this->mode = Mode::VIEW;
            }
        }
        else
        {
            if(mode == Mode::SEARCH && list)
            {
                list->Draw();
                word = list->getWord();
                if(word)
                    this->mode = Mode::VIEW;
            }
        }

        if(defButton->isPressed(true))
            app->setNextScreen(new SearchDef());
    }
    else if(mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
    // cout << mode << "\n";
}

SearchWord::SearchWord()
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->mode = Mode::NOTSEARCH;
    constexpr Vector2 origin = {300, 25};
    constexpr Vector2 size = {700, 70};
    searchbox = new SearchBox(origin, size, {WHITE});

    wordButton = new search_by_word_button({20, origin.y}, {110, 50}, PURPLE, WHITE,21);
    defButton = new search_by_def_button({20+wordButton->size.x, origin.y},  {110, 50}, WHITE,BLACK,21);

    historyButton = new history_button({10, wordButton->origin.y + wordButton->size.y + searchbox->size.y+10}, {250, 150},PINK,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button({10, historyButton->origin.y + historyButton->size.y + 10}, {250, 150},ORANGE,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button({10, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 150},DARKGREEN,"Game","Practice your vocabulary skills",BLACK,24);

    resetButton = new reset_button({10, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, GREEN,BLACK,24);
    // cout << gamesButton->origin.y + gamesButton->size.y + 90 << "\n";

    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(mode_origin, mode_size, WHITE,BLACK,25);
}


SearchWord::~SearchWord()
{
    delete searchbox;
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete list;
    delete viewScreen;
}

void SearchDef::Render(App* app)
{
    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(viewScreen)
        {
            delete viewScreen;
            viewScreen = nullptr;
        }
        if(word)
            word = nullptr;
        searchbox->DrawBox();
        searchbox->HandleInput(searchbox->buffer, searchbox->bufflen);
        searchbox->DrawInput();
        
        modesButtons->Draw();

        defButton->Draw();
        wordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();


        if(historyButton->isPressed(true)) {
            app->setNextScreen(new HistoryScreen);
        }

        if(favoriteButton->isPressed(true)) {
            app->setNextScreen(new FavoriteScreen);
        }

        if(resetButton->isPressed(true)) {
            app->setNextScreen(new ResetWarning);
        }

        if(!searchbox->state)
        {
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                // delete word;
                word = nullptr;
                list = new WordList(app->dict->searchDef(searchbox->input));
                mode = Mode::SEARCH;
            }
            if(mode == Mode::SEARCH && !searchbox->startSearch && list)
            {
                list->Draw();
                word = list->getWord();
                if(word)
                    this->mode = Mode::VIEW;
            }
        }
        else
        {
            if(mode == Mode::SEARCH && list)
            {
                list->Draw();
                word = list->getWord();
                if(word)
                    this->mode = Mode::VIEW;
            }
        }

        if(wordButton->isPressed(true))
            app->setNextScreen(new SearchWord());
        }
    else if(mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
}

SearchDef::SearchDef()
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->mode = Mode::NOTSEARCH;
    constexpr Vector2 origin = {300, 25};
    constexpr Vector2 size = {700, 70};
    searchbox = new SearchBox(origin, size, WHITE);
    wordButton = new search_by_word_button({20, origin.y}, {110, 50}, WHITE, BLACK,21);
    defButton = new search_by_def_button({20+wordButton->size.x, origin.y},  {110, 50}, PURPLE,WHITE,21);

    historyButton = new history_button({10, wordButton->origin.y + wordButton->size.y + searchbox->size.y+10}, {250, 150},PINK,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button({10, historyButton->origin.y + historyButton->size.y + 10}, {250, 150},ORANGE,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button({10, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 150},DARKGREEN,"Game","Practice your vocabulary skills",BLACK,24);

    resetButton = new reset_button({10, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, GREEN,BLACK,24);
    // cout << gamesButton->origin.y + gamesButton->size.y + 90 << "\n";

    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(mode_origin, mode_size, WHITE,BLACK,25);
}

SearchDef::~SearchDef()
{
    delete searchbox;
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete list;
    delete viewScreen;
}

App::App()
: mode(1), dict(new Dictionary())
{
    if(GetWindowHandle())
        return;
    dict->loadData(ENGENG);
    SetTargetFPS(60);
    InitWindow(1200, 800, "DICTIONARY");
    currentScreen = new SearchWord();
    
}

App::~App()
{
    if(!GetWindowHandle())
        return;
    CloseWindow();
    delete currentScreen;
    delete dict;
}

bool App::AppShouldClose()
{
    return WindowShouldClose();
}

void App::Tick()
{
    BeginDrawing();
    App::Draw();
    App::Update();
    EndDrawing();
}

void App::Draw()
{
    ClearBackground(RAYWHITE);
}

void App::Update()
{
    this->render(this->currentScreen);
}

void App::run()
{
    while(!this->AppShouldClose())
    {
        this->Tick();
    }
}

void App::setNextScreen(Screen* nextScreen)
{
    delete currentScreen;
    this->currentScreen = nextScreen;
}

void App::render(Screen* screen)
{
    screen->Render(this);
}

void ResetWarning::Render(App* app)
{
    Vector2 _origin = {300, 250};
    Vector2 _size = {600, 200};
    ClearBackground(LIGHTGRAY);
    DrawRectangle(_origin.x, _origin.y, _size.x, _size.y, WHITE);
    DrawText("Are you sure you want to reset?", _origin.x + 40, _origin.y + 30, 30, BLACK);
    DrawRectangle(_origin.x + 140, _origin.y + 140, 120, 40, WHITE);
    DrawRectangleLinesEx({_origin.x + 140, _origin.y + 140, 120, 40}, 3, BLACK);
    DrawText("YES", _origin.x + 178, _origin.y + 153, 20, BLACK);
    DrawRectangle(_origin.x + 340, _origin.y + 140, 120, 40, WHITE);
    DrawRectangleLinesEx({_origin.x + 340, _origin.y + 140, 120, 40}, 3, BLACK);
    DrawText("NO", _origin.x + 382, _origin.y + 153, 20, BLACK);
}

void FavoriteScreen::Render(App* app)
{
    if (mode == Mode::NOTSEARCH || mode == Mode::SEARCH)
    {
        Vector2 _origin = {50, 80};
        Vector2 _size = {900, 100};
        ClearBackground(RAYWHITE);
        DrawRectangle(_origin.x, _origin.y, _size.x, _size.y, BLUE);
        DrawText("Favorite", _origin.x + 10, _origin.y + (_size.y - 36)/2, 48, LIGHTGRAY);
        backButton->Draw();
        // delete word;

        if (!list)
            list = new WordList(app->dict->viewFavList());
    
        list->Draw();

        word = list->getWord();
        if(word)
        {
            this->mode = Mode::VIEW;
        }

        if(backButton->Update())
            app->setNextScreen(new SearchDef);
    }
    if (mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
    
}

FavoriteScreen::FavoriteScreen()
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->mode = Mode::NOTSEARCH;
    backButton = new ReturnButton({1050, 112}, {45, 45}, RAYWHITE);
}

FavoriteScreen::~FavoriteScreen()
{

}

void HistoryScreen::Render(App* app)
{
    Vector2 _origin = {50, 80};
    Vector2 _size = {1100, 100};
    ClearBackground(RAYWHITE);
    DrawRectangle(_origin.x, _origin.y, _size.x, _size.y, BLUE);
    DrawText("History", _origin.x + 10, _origin.y + (_size.y - 36)/2, 48, LIGHTGRAY);
    Vector2 return_origin = {50, 10};
    Vector2 return_size = {100, 50};
    DrawRectangle(return_origin.x, return_origin.y, return_size.x, return_size.y, RED);
}