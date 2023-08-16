// app.cpp
#include "App.h"

State::State()
: mode(1), dataset(1)
{}

void SearchWord::Render(App* app)
{
    searchbox->DrawBox();
    searchbox->HandleInput(searchbox->buffer, searchbox->bufflen);
    searchbox->DrawInput();
    defButton->Draw();
    wordButton->Draw();
    historyButton->Draw();
    favoriteButton->Draw();
    gamesButton->Draw();
    resetButton->Draw();
    modesButtons->Draw();
}
SearchWord::SearchWord()
{
    constexpr Vector2 origin = {50, 80};
    constexpr Vector2 size = {1100, 100};
    searchbox = new SearchBox(origin, size, GRAY);

    defButton = new search_by_def_button({origin.x, origin.y + size.y + 20}, {200, 75}, GRAY);

    wordButton = new search_by_word_button({origin.x, defButton->origin.y + defButton->size.y + 15}, {200, 75}, GRAY);

    historyButton = new history_button({origin.x, wordButton->origin.y + wordButton->size.y + 15}, {200, 75}, GRAY);

    favoriteButton = new favorite_button({origin.x, historyButton->origin.y + historyButton->size.y + 15}, {200, 75}, GRAY);

    gamesButton = new games_button({origin.x, favoriteButton->origin.y + favoriteButton->size.y + 15}, {200, 75}, GRAY);

    resetButton = new reset_button({origin.x, gamesButton->origin.y + gamesButton->size.y + 15}, {200, 75}, GRAY);

    constexpr Vector2 mode_origin = {50, 30};
    constexpr Vector2 mode_size = {200, 45};
    modesButtons = new modes_buttons(mode_origin, mode_size, WHITE);
}

SearchWord::~SearchWord()
{
    delete searchbox;
    delete defButton;
}
App::App()
: mode(1)
{
    if(GetWindowHandle())
        return;
    SetTargetFPS(60);
    InitWindow(1200, 800, "DICTIONARY");
    currentScreen = new SearchWord();
}

App::~App()
{
    if(!GetWindowHandle())
        return;
    CloseWindow();
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