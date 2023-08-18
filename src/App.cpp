// app.cpp
#include "App.h"

State::State()
: mode(1), dataset(1)
{}

void SearchWord::Render(App* app)
{
    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(word)
            word = nullptr;
        searchbox->DrawBox();
        searchbox->HandleInput(searchbox->buffer, searchbox->bufflen);
        searchbox->DrawInput();
        defButton->Draw();

        wordButton->DrawSearch();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        modesButtons->Draw();

        if(!searchbox->state)
        {
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                list = new WordList(app->dict->searchWord(searchbox->input));
                mode = Mode::SEARCH;
            }
            if(mode == Mode::SEARCH && !searchbox->startSearch && list)
            {
                list->Draw();
                word = list->getWord();
            }
        }
        else
        {
            if(mode == Mode::SEARCH && list)
            {
                list->Draw();
                word = list->getWord();
            }
        }

        if(defButton->isPressed())
            app->setNextScreen(new SearchDef());
    }
}
SearchWord::SearchWord()
: mode(Mode::NOTSEARCH), word(nullptr), list(nullptr)
{
    constexpr Vector2 origin = {50, 120};
    constexpr Vector2 size = {1100, 85};
    searchbox = new SearchBox(origin, size, {212,212,212,255});
    defButton = new search_by_def_button({origin.x, origin.y + size.y + 30}, {200, 75}, GRAY);

    wordButton = new search_by_word_button({origin.x, defButton->origin.y + defButton->size.y + 15}, {200, 75}, GRAY);

    historyButton = new history_button({origin.x, wordButton->origin.y + wordButton->size.y + 15}, {200, 75}, GRAY);

    favoriteButton = new favorite_button({origin.x, historyButton->origin.y + historyButton->size.y + 15}, {200, 75}, GRAY);

    gamesButton = new games_button({origin.x, favoriteButton->origin.y + favoriteButton->size.y + 15}, {200, 75}, GRAY);

    resetButton = new reset_button({origin.x, gamesButton->origin.y + gamesButton->size.y + 15}, {200, 75}, GRAY);
    // cout << gamesButton->origin.y + gamesButton->size.y + 90 << "\n";

    constexpr Vector2 mode_origin = {50, 50};
    constexpr Vector2 mode_size = {200, 45};
    modesButtons = new modes_buttons(mode_origin, mode_size, WHITE);
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
}

void SearchDef::Render(App* app)
{
    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(word)
            word = nullptr;
        searchbox->DrawBox();
        searchbox->HandleInput(searchbox->buffer, searchbox->bufflen);
        searchbox->DrawInput();
        defButton->DrawSearch();

        wordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        modesButtons->Draw();

        if(!searchbox->state)
        {
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                list = new WordList(app->dict->searchDef(searchbox->input));
                mode = Mode::SEARCH;
            }
            if(mode == Mode::SEARCH && !searchbox->startSearch && list)
            {
                list->Draw();
                word = list->getWord();
            }
        }
        else
        {
            if(mode == Mode::SEARCH && list)
            {
                list->Draw();
                word = list->getWord();
            }
        }
        if(wordButton->isPressed())
            app->setNextScreen(new SearchWord());
    }
}

SearchDef::SearchDef()
: mode(Mode::NOTSEARCH), word(nullptr), list(nullptr)
{
    constexpr Vector2 origin = {50, 120};
    constexpr Vector2 size = {1100, 85};
    searchbox = new SearchBox(origin, size, {212,212,212,255});
    defButton = new search_by_def_button({origin.x, origin.y + size.y + 30}, {200, 75}, GRAY);

    wordButton = new search_by_word_button({origin.x, defButton->origin.y + defButton->size.y + 15}, {200, 75}, GRAY);

    historyButton = new history_button({origin.x, wordButton->origin.y + wordButton->size.y + 15}, {200, 75}, GRAY);

    favoriteButton = new favorite_button({origin.x, historyButton->origin.y + historyButton->size.y + 15}, {200, 75}, GRAY);

    gamesButton = new games_button({origin.x, favoriteButton->origin.y + favoriteButton->size.y + 15}, {200, 75}, GRAY);

    resetButton = new reset_button({origin.x, gamesButton->origin.y + gamesButton->size.y + 15}, {200, 75}, GRAY);
    // cout << gamesButton->origin.y + gamesButton->size.y + 90 << "\n";

    constexpr Vector2 mode_origin = {50, 50};
    constexpr Vector2 mode_size = {200, 45};
    modesButtons = new modes_buttons(mode_origin, mode_size, WHITE);
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
}

App::App()
: mode(1), dict(new Dictionary())
{
    if(GetWindowHandle())
        return;
    SetTargetFPS(60);
    InitWindow(1200, 800, "DICTIONARY");
    currentScreen = new SearchWord();
    dict->loadData(ENGENG);
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