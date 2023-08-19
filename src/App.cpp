// app.cpp
#include "App.h"

State::State()
: mode(1), dataset(1)
{}

void SearchWord::Render(App* app)
{
    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(word)
            word = nullptr;
        searchbox->DrawBox();
        searchbox->HandleInput(searchbox->buffer, searchbox->bufflen);
        searchbox->DrawInput();
        modesButtons->Draw();
        defButton->Draw();

        wordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();
        if(historyButton->isPressed()) {
            app->setNextScreen(new HistoryScreen);
        }

        if(favoriteButton->isPressed()) {
            app->setNextScreen(new FavoriteScreen);
        }

        if(resetButton->isPressed()) {
            app->setNextScreen(new ResetWarning);
        }

        if(!searchbox->state)
        {
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                list = new WordList(app->dict->searchWord(searchbox->input));
                cout<<"search";
                mode = Mode::SEARCH;
            }
            if(mode == Mode::SEARCH && !searchbox->startSearch && list)
            {
                list->Draw();
                word = list->getWord();

            }
        }
        else
        {
            if(mode == Mode::SEARCH && list)
            {
                cout<<"testneee";
                list->Draw();
                word = list->getWord();

            }
        }

        if(defButton->isPressed())
            app->setNextScreen(new SearchDef());
    }
}

SearchWord::SearchWord()
: mode(Mode::NOTSEARCH), word(nullptr), list(nullptr)
{
    constexpr Vector2 origin = {300, 25};
    constexpr Vector2 size = {700, 70};
    searchbox = new SearchBox(origin, size, WHITE);

    wordButton = new search_by_word_button({20, origin.y}, {110, 50}, PURPLE, WHITE,21);
    defButton = new search_by_def_button({20+wordButton->size.x, origin.y},  {110, 50}, WHITE,BLACK,21);

    historyButton = new history_button({10, wordButton->origin.y + wordButton->size.y + searchbox->size.y+10}, {250, 150},PINK,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button({10, historyButton->origin.y + historyButton->size.y + 10}, {250, 150},ORANGE,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button({10, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 150},DARKGREEN,"Game","Practice your vocabulary skills",BLACK,24);

    resetButton = new reset_button({10, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, GREEN,BLACK,24);
    // cout << gamesButton->origin.y + gamesButton->size.y + 90 << "\n";
    
    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(mode_origin, mode_size, WHITE,BLACK,25);

}


SearchWord::~SearchWord()
{
    delete searchbox;
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete list;
}

void SearchDef::Render(App* app)
{
    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(word)
            word = nullptr;
        searchbox->DrawBox();
        searchbox->HandleInput(searchbox->buffer, searchbox->bufflen);
        searchbox->DrawInput();
        defButton->Draw();

        wordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        modesButtons->Draw();



        if(!searchbox->state)
        {
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                list = new WordList(app->dict->searchDef(searchbox->input));
                mode = Mode::SEARCH;
            }
            if(mode == Mode::SEARCH && !searchbox->startSearch && list)
            {
                list->Draw();
                word = list->getWord();
            }
        }
        else
        {
            if(mode == Mode::SEARCH && list)
            {
                list->Draw();
                word = list->getWord();
            }
        }

        if(wordButton->isPressed())
            app->setNextScreen(new SearchWord());
        }
}

SearchDef::SearchDef()
: mode(Mode::NOTSEARCH), word(nullptr), list(nullptr)
{
 constexpr Vector2 origin = {300, 25};
    constexpr Vector2 size = {700, 70};
    searchbox = new SearchBox(origin, size, WHITE);

    wordButton = new search_by_word_button({20, origin.y}, {110, 50}, WHITE, BLACK,21);
    defButton = new search_by_def_button({20+wordButton->size.x, origin.y},  {110, 50}, PURPLE,WHITE,21);

    historyButton = new history_button({10, wordButton->origin.y + wordButton->size.y + searchbox->size.y+10}, {250, 150},PINK,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button({10, historyButton->origin.y + historyButton->size.y + 10}, {250, 150},ORANGE,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button({10, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 150},DARKGREEN,"Game","Practice your vocabulary skills",BLACK,24);

    resetButton = new reset_button({10, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, GREEN,BLACK,24);
    // cout << gamesButton->origin.y + gamesButton->size.y + 90 << "\n";
    
    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(mode_origin, mode_size, WHITE,BLACK,25);
}

SearchDef::~SearchDef()
{
    delete searchbox;
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete list;
}

App::App()
: mode(1), dict(new Dictionary())
{
    if(GetWindowHandle())
        return;
    SetTargetFPS(60);
    InitWindow(1200, 800, "DICTIONARY");
    currentScreen = new SearchWord();
    dict->loadData(ENGENG);
}

App::~App()
{
    if(!GetWindowHandle())
        return;
    CloseWindow();
    delete currentScreen;
    delete dict;
}

bool App::AppShouldClose()
{
    return WindowShouldClose();
}

void App::Tick()
{
    BeginDrawing();
    App::Draw();
    App::Update();
    EndDrawing();
}

void App::Draw()
{
    ClearBackground(GREY);
}

void App::Update()
{
    this->render(this->currentScreen);
}

void App::run()
{
    while(!this->AppShouldClose())
    {
        this->Tick();
    }
}

void App::setNextScreen(Screen* nextScreen)
{
    delete currentScreen;
    this->currentScreen = nextScreen;
}

void App::render(Screen* screen)
{
    screen->Render(this);
}

