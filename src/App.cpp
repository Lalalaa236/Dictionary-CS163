#include "App.h"

State::State()
: change(false), dataset(ENGENG)
{}

ViewWord::ViewWord(WordButton* word, Screen* screen, App* app)
: word(word), screen(screen), app(app), showable(), origin({150, 180})
{
    SetShowable();
    backButton = new ReturnButton(app->asset, {1050, 112}, {45, 45}, RAYWHITE);
    favButton = new FavButton(app->asset, {1050, 652}, {45, 45}, word->data);
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
            this->app->dict->removeFromFavList(word->data, this->app->state.dataset);
            word->cur = app->asset->base; //marking
        }
    }
    else
    {
        if(favButton->Update(word->data))
        {
            this->app->dict->addToFavList(word->data, this->app->state.dataset);
            // cout << "welp";
            word->cur = app->asset->faved;
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
        //cout << "fuck\n";

        defButton->Draw();
        wordButton->Draw();

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(historyButton->isPressed(false)) {
            app->setNextScreen(new HistoryScreen(this->app));
        }

        if(favoriteButton->isPressed(false)) {
            app->setNextScreen(new FavoriteScreen(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        if(!searchbox->state)
        {
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                // delete word;
                word = nullptr;
                list = new WordList(app->asset, app->dict->searchWord(searchbox->input));
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
            app->setNextScreen(new SearchDef(this->app));
    }
    else if(mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
    // cout << mode << "\n";
}

SearchWord::SearchWord(App* app)
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {700, 70};
    searchbox = new SearchBox(origin, size, {WHITE});

    wordButton = new search_by_word_button(this->app->asset, {30, origin.y }, {125, 70}, PURPLE, WHITE,21);
    defButton = new search_by_def_button(this->app->asset, {30+wordButton->size.x, origin.y },  {125, 70}, WHITE,BLACK,21);

    addWordButton = new add_word_button(this->app->asset, {30, wordButton->origin.y + wordButton->size.y + searchbox->size.y - 10}, {250, 100},SKYBLUE,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(this->app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},PINK,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(this->app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},ORANGE,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(this->app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},DARKGREEN,"Game","Practice your vocabulary skills",BLACK,24);

    resetButton = new reset_button(this->app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, {158,210,190,255},BLACK,24);
    // cout << gamesButton->origin.y + gamesButton->size.y + 90 << "\n";

    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(this->app->asset, mode_origin, mode_size, WHITE,BLACK,25);
    //cout << "jesus christ!\n";
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

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(historyButton->isPressed(false)) {
            app->setNextScreen(new HistoryScreen(this->app));
        }

        if(favoriteButton->isPressed(false)) {
            app->setNextScreen(new FavoriteScreen(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        if(!searchbox->state)
        {
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                // delete word;
                word = nullptr;
                list = new WordList(app->asset, app->dict->searchDef(searchbox->input));
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
            app->setNextScreen(new SearchWord(this->app));
        }
    else if(mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
}

SearchDef::SearchDef(App* app)
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {700, 70};
    searchbox = new SearchBox(origin, size, WHITE);
    wordButton = new search_by_word_button(app->asset, {30, origin.y },  {125, 70}, WHITE,BLACK,21);
    defButton = new search_by_def_button(app->asset, {30+wordButton->size.x, origin.y }, {125, 70}, PURPLE, WHITE,21);

    addWordButton = new add_word_button(app->asset, {30, wordButton->origin.y + wordButton->size.y + searchbox->size.y - 10}, {250, 100},SKYBLUE,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},PINK,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},ORANGE,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},DARKGREEN,"Game","Practice your vocabulary skills",BLACK,24);

    resetButton = new reset_button(app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, {158,210,190,255},BLACK,24);

    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(app->asset, mode_origin, mode_size, WHITE,BLACK,25);
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
    asset = new Asset();
    currentScreen = new SearchWord(this);
}

App::~App()
{
    if(!GetWindowHandle())
        return;
    CloseWindow();
    delete currentScreen;
    delete dict;
    delete asset;
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
    ClearBackground(GREY);
}

void App::Update()
{
    this->render(this->currentScreen);
}

void App::run()
{
    while(!this->AppShouldClose())
    {
        if(this->state.change)
        {
            this->state.change = false;
            dict->deleteDict();
            dict->loadData(this->state.dataset);
        }
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
    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        ClearBackground(GREY);

        if(viewScreen)
        {
            delete viewScreen;
            viewScreen = nullptr;
        }
        if(word)
            word = nullptr;

        defButton->Draw();
        wordButton->Draw();

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(historyButton->isPressed(false)) {
            app->setNextScreen(new HistoryScreen(this->app));
        }
        
        if(defButton->isPressed(false))
        {
            app->setNextScreen(new SearchDef(this->app));
        }

        if(wordButton->isPressed(false))
        {
            app->setNextScreen(new SearchWord(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        Vector2 _origin = {300, 50};
        Vector2 _size = {850, 70};
        ClearBackground(RAYWHITE);
        DrawRectangle(_origin.x, _origin.y, _size.x, _size.y, ORANGE);
        DrawText("  Favorite", _origin.x + 10, _origin.y + (_size.y - 36)/2, 48, WHITE);
        // backButton->Draw();
        // delete word;

        if (!list)
            list = new WordList(app->asset, app->dict->viewFavList());
    
        list->Draw();

        word = list->getWord();
        if(word)
        {
            this->mode = Mode::VIEW;
        }

        // if(backButton->Update())
        //     app->setNextScreen(new SearchDef);
    }
    if (mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
    
}

FavoriteScreen::FavoriteScreen(App* app)
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    // backButton = new ReturnButton({1050, 112}, {45, 45}, RAYWHITE);

    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {700, 70};

    wordButton = new search_by_word_button(app->asset, {30, origin.y },  {125, 70}, {114,93,255,255}, WHITE,21);
    defButton = new search_by_def_button(app->asset, {30 + wordButton->size.x, origin.y }, {125, 70}, {114,93,255,255}, WHITE,21);

    addWordButton = new add_word_button(app->asset, {30, wordButton->origin.y + wordButton->size.y + 60}, {250, 100},SKYBLUE,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},PINK,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},ORANGE,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},DARKGREEN,"Game","Practice your vocabulary skills",BLACK,24);

    resetButton = new reset_button(app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, {158,210,190,255},BLACK,24);

}

FavoriteScreen::~FavoriteScreen()
{
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete list;
    delete viewScreen;
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

void AddWord::Render(App* app)
{
    Vector2 _origin = {50, 80};
    Vector2 _size = {1100, 100};
    ClearBackground(RAYWHITE);
    DrawRectangle(_origin.x, _origin.y, _size.x, _size.y, BLUE);
    DrawText("Add a Word", _origin.x + 10, _origin.y + (_size.y - 36)/2, 48, LIGHTGRAY);
    Vector2 return_origin = {50, 10};
    Vector2 return_size = {100, 50};
    DrawRectangle(return_origin.x, return_origin.y, return_size.x, return_size.y, RED);
}

HistoryScreen::HistoryScreen(App* app)
{
    this->app = app;
}

ResetWarning::ResetWarning(App* app)
{
    this->app = app;
}

AddWord::AddWord(App* app)
{
    this->app = app;
}