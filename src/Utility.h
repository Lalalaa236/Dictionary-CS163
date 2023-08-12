#ifndef SCREEN_H
#define SCREEN_H

#include "Dictionary.h"
#include "raylib.h"
#include "SearchBox.h"
#include "App.h"
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

class SearchWord
{
    SearchBox searchbox;

    SearchWord();
    void Render(App* app);
};

#endif