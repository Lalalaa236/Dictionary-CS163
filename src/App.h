#pragma once

#ifndef APP_H
#define APP_H

#include "Dictionary.h"
#include "raylib.h"
#include "SearchBox.h"
#include <assert.h>
#include "Button.h"
#include "WordList.h"

const string ENGENG = "data\\Eng-Eng\\";
const string ENGVIE = "data\\Eng-Vie\\";
const string VIEENG = "data\\Vie-Eng\\";
const string SLANG = "data\\Slang\\";
const string EMOJI = "data\\Emoji\\";

class App;

class State
{
public:
    bool change;
    string dataset;
    
    State();
};

class Screen
{
public:
    App* app;
    enum Mode {NOTSEARCH = 0, SEARCH = 1, VIEW = 2};
    int mode;
    virtual void Render(App* app) = 0;
};

class ViewWord
{
private:
    WordButton* word;
    Screen* screen;
    App* app;
    Rectangle rect;
    string showable;
    Vector2 origin;
    ReturnButton* backButton;
    FavButton* favButton;
    remove_button* removeButton;
public:
    ~ViewWord();
    ViewWord(WordButton* word, Screen* screen, App* app);
    void Render(App* app, Screen* screen);
    void SetShowable();
    int findNearestSpace(const string& s, int length, int pos);
    void Update();
    //Word* getWord();
};


class SearchWord : public Screen
{
private:
    // enum Mode {NOTSEARCH = 0, SEARCH = 1, VIEW = 2};
    // int mode;
    SearchBox* searchbox;
    search_by_def_button* defButton; 
    search_by_word_button* wordButton;
    history_button* historyButton;
    favorite_button* favoriteButton;
    games_button* gamesButton;
    reset_button* resetButton;
    add_word_button* addWordButton;
    modes_buttons* modesButtons;
    WordList* list;
    WordButton* word;
    ViewWord* viewScreen;
    ShuffleButton* shuffleButton;
public:
    SearchWord(App* app);
    ~SearchWord();
    void Render(App* app);
};

class SearchDef : public Screen
{
private:
    // enum Mode {NOTSEARCH = 0, SEARCH = 1, VIEW = 2};
    // int mode;
    SearchBox* searchbox;
    search_by_def_button* defButton; 
    search_by_word_button* wordButton;
    add_word_button* addWordButton;
    history_button* historyButton;
    favorite_button* favoriteButton;
    games_button* gamesButton;
    reset_button* resetButton;
    modes_buttons* modesButtons;
    WordList* list;
    WordButton* word;
    ViewWord* viewScreen;
    ShuffleButton* shuffleButton;
public:
    SearchDef(App* app);
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
    Asset* asset;
    
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
private:
    search_by_def_button* defButton; 
    search_by_word_button* wordButton;
    add_word_button* addWordButton;
    history_button* historyButton;
    favorite_button* favoriteButton;
    games_button* gamesButton;
    reset_button* resetButton;
    modes_buttons* modesButtons;
    ReturnButton* backButton;
    WordList* list;
    WordButton* word;
    ViewWord* viewScreen;
    vector<Word*> his;
public:
    HistoryScreen(App* app);
    ~HistoryScreen();
    void Render(App* app);
};

class FavoriteScreen : public Screen
{
private:
    search_by_def_button* defButton; 
    search_by_word_button* wordButton;
    add_word_button* addWordButton;
    history_button* historyButton;
    favorite_button* favoriteButton;
    games_button* gamesButton;
    reset_button* resetButton;
    modes_buttons* modesButtons;
    ReturnButton* backButton;
    WordList* list;
    WordButton* word;
    ViewWord* viewScreen;
public:
    FavoriteScreen(App* app);
    ~FavoriteScreen();
    void Render(App* app);
};

class ResetWarning : public Screen
{
private:
    YesNo_button* YesBtn;
    YesNo_button* NoBtn;
public:
    void Render(App* app);

    ResetWarning(App* app);
    ~ResetWarning();
};
class AddWord:public Screen
{
    private:
    Rectangle rect;
    string showable;
    Vector2 origin;
    ReturnButton* backButton;
    AddWordScreen* addwordScreen;
   public:
    AddWord(App* app);
    ~AddWord();
    void Render(App* app);
    //Word* getWord();
}; 
#endif