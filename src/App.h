#ifndef APP_H
#define APP_H

#include "Utility.h"
#include "SearchBox.h"

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