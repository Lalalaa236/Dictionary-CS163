#ifndef APP_H
#define APP_H

#include "Dictionary.h"
#include "raylib.h"
#include "SearchBox.h"
#include <assert.h>

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

// void setNextScreen(App* app, Screen* nextScreen);
// void render(App* app, Screen* screen);

#endif