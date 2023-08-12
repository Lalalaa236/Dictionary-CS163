#include "App.h"

App::App()
: mode(1)
{
    if(!GetWindowHandle())
        return;
    SetTargetFPS(60);
    InitWindow(1200, 800, "DICTIONARY");
}

App::~App()
{
    if(GetWindowHandle)
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