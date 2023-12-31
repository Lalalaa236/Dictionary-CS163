#pragma once

#ifndef APP_H
#define APP_H

#include "Dictionary.h"
#include "raylib.h"
#include "SearchBox.h"
#include <assert.h>
#include "Button.h"
#include "WordList.h"
#include "DefList.h"

const string ENGENG = "data\\Eng-Eng\\";
const string ENGVIE = "data\\Eng-Vie\\";
const string VIEENG = "data\\Vie-Eng\\";
const string SLANG = "data\\Slang\\";
const string EMOJI = "data\\Emoji\\";

class App;
class ViewDef;
class EditDefScreen;

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
public:
    enum Mode {VIEW = 0, EDIT = 1};
    int mode;
    WordButton* word;
    Screen* screen;
    App* app;
    Rectangle rect;
    string showable;
    Vector2 origin;
    ReturnButton* backButton;
    FavButton* favButton;
    remove_button* removeButton;
    EditButton* editbutton;
    ViewDef* viewdef;
    ~ViewWord();
    ViewWord(WordButton* word, Screen* screen, App* app);
    void Render(App* app, Screen* screen);
    void SetShowable();
    int findNearestSpace(const string& s, int length, int pos);
    void Update();
    //Word* getWord();
};

class ViewDef
{
public:
    enum Mode {VIEW = 0, EDIT = 1};
    int mode;
    ReturnButton* backButton;
    ViewWord* originalScreen;
    Vector2 origin;
    Word* word;
    DefList* deflist;
    EditDefScreen* editscreen;
    Asset* asset;

    ViewDef(ViewWord* originalScreen);
    ~ViewDef();

    void Render();
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

class EditDefScreen
{
public:
    SaveButton* savebutton;
    Vector2 origin;
    ViewDef* viewdef;
    Word* word;
    Definition* def;
    EditDefButton* chosen;
    bool is_enter_def;

    string input_def;
    string showable;

    int bufflen_def;
    Rectangle def_rec;
    Asset* asset;
    EditDefScreen(Asset* asset, EditDefButton* chosen, ViewDef* viewdef)
    : asset(asset), chosen(chosen), viewdef(viewdef), is_enter_def(false)
    {
        origin = {30, 70};
        def = chosen->def;
        word = chosen->def->word;
        input_def = def->data;
        SetShowable();
        //strcpy(buffer_def, def->data.c_str());
        bufflen_def = def->data.length();
        //cout << "bufflen: " << bufflen_def << "!\n";
        def_rec = {30, origin.y+70, 1100, 600};
        savebutton = new SaveButton(asset, {1030, 120}, {40, 40}, BLACK);
    }
    ~EditDefScreen();
    float cursorBlinkTime = 0.0f;
    void CursorBlink(float time);
    void SetShowable();
    void Draw();//char* input_def, int& length_def);
    void Update();
};

class GameScreen : public Screen
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
    WordButton* word;
    ViewWord* viewScreen;
    Guess_button* guessDefBtn;
    Guess_button* guessWordBtn;
public:
    bool isDrop = false;
    GameScreen(App* app);
    ~GameScreen();
    void Render(App* app);
};

class GuessDefScreen : public Screen
{
private:
    enum ModeGame {PREPARE = 0, START = 1, RIGHT = 2, WRONG = 3, MIDPHASE = 4};
    int modeGame;
    search_by_def_button* defButton; 
    search_by_word_button* wordButton;
    add_word_button* addWordButton;
    history_button* historyButton;
    favorite_button* favoriteButton;
    games_button* gamesButton;
    reset_button* resetButton;
    modes_buttons* modesButtons;
    ReturnButton* backButton;
    WordButton* word;
    ViewWord* viewScreen;
    Guess_button* guessDefBtn;
    Guess_button* guessWordBtn;
    YesNo_button* yesBtn;
    YesNo_button* noBtn;
    Word* gameWord;
    string def_ans;
    int pos_ans;
    vector<string> multi_choices;
    Choices_button* firstChoice;
    Choices_button* secondChoice;
    Choices_button* thirdChoice;
    Choices_button* fourthChoice;
    int counter;
    // Word* word, string def_ans, int pos_ans, vector<string> multi_choices
public:
    GuessDefScreen(App* app);
    ~GuessDefScreen();
    void Render(App* app);
};

class GuessWordScreen : public Screen
{
private:
    enum ModeGame {PREPARE = 0, START = 1, RIGHT = 2, WRONG = 3, MIDPHASE = 4};
    int modeGame;
    search_by_def_button* defButton; 
    search_by_word_button* wordButton;
    add_word_button* addWordButton;
    history_button* historyButton;
    favorite_button* favoriteButton;
    games_button* gamesButton;
    reset_button* resetButton;
    modes_buttons* modesButtons;
    ReturnButton* backButton;
    WordButton* word;
    ViewWord* viewScreen;
    Guess_button* guessDefBtn;
    Guess_button* guessWordBtn;
    YesNo_button* yesBtn;
    YesNo_button* noBtn;
    Definition* gameDef;
    string def_ans;
    int pos_ans;
    vector<string> multi_choices;
    Choices_button* firstChoice;
    Choices_button* secondChoice;
    Choices_button* thirdChoice;
    Choices_button* fourthChoice;
    int counter;
public:
    GuessWordScreen(App* app);
    ~GuessWordScreen();
    void Render(App* app);
};

#endif