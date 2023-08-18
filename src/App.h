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

class ViewWord
{
private:
    Word* word;
    Screen* screen;
    App* app;
    Rectangle rect;
    string showable;
    Vector2 origin;
public:
    ViewWord();
    ViewWord(Word* word, Screen* screen, App* app);
    void Render(App* app, Screen* screen);
    void SetShowable();
    int findNearestSpace(const string& s, int length, int pos);
    void Update();
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
    ViewWord* viewScreen;
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
    void Render(App* app);
};

class FavoriteScreen : public Screen
{
public:
    void Render(App* app);
};

class ResetWarning : public Screen
{
public:
    void Render(App* app);
};

#endif