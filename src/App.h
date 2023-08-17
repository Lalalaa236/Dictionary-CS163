#pragma once

#ifndef APP_H
#define APP_H

#include "Dictionary.h"
#include "raylib.h"
#include "SearchBox.h"
#include <assert.h>
#include "Button.h"
#include "WordList.h"

const string ENGENG = "data\\Eng-Eng.txt";

class App;

class State
{
public:
    int mode;
    int dataset;
    
    State();
};

class Screen
{
public:
    virtual void Render(App* app) = 0;
};

class SearchWord : public Screen
{
private:
    enum Mode {NOTSEARCH = 0, SEARCH = 1, VIEW = 2};
    int mode;
    SearchBox* searchbox;
    search_by_def_button* defButton; 
    search_by_word_button* wordButton;
    history_button* historyButton;
    favorite_button* favoriteButton;
    games_button* gamesButton;
    reset_button* resetButton;
    modes_buttons* modesButtons;
    WordList* list;
    Word* word;
public:
    SearchWord();
    ~SearchWord();
    void Render(App* app);
};

class SearchDef : public Screen
{
private:
    enum Mode {NOTSEARCH = 0, SEARCH = 1, VIEW = 2};
    int mode;
    SearchBox* searchbox;
    search_by_def_button* defButton; 
    search_by_word_button* wordButton;
    history_button* historyButton;
    favorite_button* favoriteButton;
    games_button* gamesButton;
    reset_button* resetButton;
    modes_buttons* modesButtons;
    WordList* list;
    Word* word;
public:
    SearchDef();
    ~SearchDef();
    void Render(App* app);
};

class App
{
public:
    State state;
    Screen* currentScreen;
    int mode;
    Dictionary* dict;
    
    App();
    ~App();

    void run();
    bool AppShouldClose();
    void Tick();
    void Draw();
    void Update();
    void setNextScreen(Screen* nextScreen);
    void render(Screen* screen);
};

class HistoryScreen : public Screen
{
public:
    void Render(App* app)
    {
        Vector2 _origin = {50, 80};
        Vector2 _size = {1100, 100};
        ClearBackground(RAYWHITE);
        DrawRectangle(_origin.x, _origin.y, _size.x, _size.y, BLUE);
        DrawText("History", _origin.x + 10, _origin.y + (_size.y - 36)/2, 48, LIGHTGRAY);
        Vector2 return_origin = {50, 10};
        Vector2 return_size = {100, 50};
        DrawRectangle(return_origin.x, return_origin.y, return_size.x, return_size.y, RED);
    };
};

class FavoriteScreen : public Screen
{
public:
    void Render(App* app) 
    {
        Vector2 _origin = {50, 80};
        Vector2 _size = {1100, 100};
        ClearBackground(RAYWHITE);
        DrawRectangle(_origin.x, _origin.y, _size.x, _size.y, BLUE);
        DrawText("Favorite", _origin.x + 10, _origin.y + (_size.y - 36)/2, 48, LIGHTGRAY);
    }
};

class ResetWarning : public Screen
{
public:
    void Render(App* app)
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
};

#endif