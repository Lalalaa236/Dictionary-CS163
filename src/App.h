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
public:
    SearchBox* searchbox;
    search_by_def_button* defButton; 
    search_by_word_button* wordButton;
    history_button* historyButton;
    favorite_button* favoriteButton;
    games_button* gamesButton;
    reset_button* resetButton;
    modes_buttons* modesButtons;
    WordList* list;
    Dictionary* dict;

    SearchWord();
    ~SearchWord();
    void Render(App* app);
};
class App
{
public:
    State state;
    Screen* currentScreen;
    int mode;
    
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

#endif