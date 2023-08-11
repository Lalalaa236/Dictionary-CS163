#ifndef SCREEN_H
#define SCREEN_H

#include "Dictionary.h"
#include "raylib.h"
#include <assert.h>

class App;

class State
{
public:
    int choice;
    bool endApp;

    State();
};

class Screen
{
public:
    virtual void Render(App* app) = 0;
};

void setNextScreen(App* app, Screen* nextScreen);
void render(App* app, Screen* screen);

#endif