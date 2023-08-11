#ifndef APP_H
#define APP_H

#include "Utility.h"

class App
{
public:
    State state;
    Screen* currentScreen;

    App();
    ~App();

    void run();
    bool AppShouldClose();
    void Tick();
    void Draw();
    void Update();
};

#endif