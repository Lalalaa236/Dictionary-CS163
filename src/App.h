#ifndef APP_H
#define APP_H

#include "Utility.h"

class App
{
public:
    State state;
    Screen* currentScreen;

    App();

    void run();
};

#endif