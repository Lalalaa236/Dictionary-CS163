#include "src/App.h"

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    App* app = new App;
    app->run();
    delete app;
    return 0;
}