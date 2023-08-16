#include "App.h"

State::State()
: mode(1), dataset(1)
{}

void SearchWord::Render(App* app)
{
    searchbox->DrawBox();
    searchbox->HandleInput(searchbox->buffer, searchbox->bufflen);
    searchbox->DrawInput();
}

SearchWord::SearchWord()
{
    constexpr Vector2 origin = {50, 30};
    constexpr Vector2 size = {1100, 100};
    searchbox = new SearchBox(origin, size, GRAY);
}

SearchWord::~SearchWord()
{
    delete searchbox;
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
    //cout << "loli";
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