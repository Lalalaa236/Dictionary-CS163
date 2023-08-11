#include "App.h"

App::App()
{
    SetTargetFPS(60);
    assert(!GetWindowHandle()); //Checks if there is already a window or not
    InitWindow(1200, 800, "DICTIONARY");
}

App::~App()
{
    assert(GetWindowHandle);
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