// app.cpp
#include "App.h"

State::State()
: mode(1), dataset(0)
{}

ViewWord::ViewWord()
: word(nullptr), screen(nullptr), app(nullptr), rect(), showable()
{}

ViewWord::ViewWord(Word* word, Screen* screen, App* app)
: word(word), screen(screen), app(app), showable(), origin({150, 150})
{
    SetShowable();
}

void ViewWord::Render(App* app, Screen* screen)
{
    DrawRectangle(80, 80, 1000, 60, DARKBLUE);
    DrawRectangleLinesEx({80, 80, 1000, 600}, 5, BLACK);
    DrawText(word->data.c_str(), 100, 100, 45, BLACK);
    
    Update();
}

void ViewWord::Update()
{
    BeginScissorMode(150, 150, 1000, 530);
    DrawText(showable.c_str(), this->origin.x, this->origin.y, 30, BLACK);
    float offset = GetMouseWheelMove() * 30;
    this->origin.y += offset;
    EndScissorMode();
}

void ViewWord::SetShowable()
{
    int size = word->defs.size();
    for(int i = 0; i < size; ++i)
    {
        string cpy = word->defs[i]->data;
        int count = 0;
        int length = cpy.length();
        for(int j = 0; j < length; ++j)
        {
            if(count == 50)
            {
                int k = findNearestSpace(cpy, length, j);
                cpy[k] = '\n';
                count = 0;
            }
            ++count;
        }
        showable.append(cpy);
        showable.append("\n\n");
    }
    int length = showable.length();
    cout << showable;
}

int ViewWord::findNearestSpace(const string& s, int length, int pos)
{
    int i = pos;
    for(; i >= 0; --i)
        if(s[i] == ' ')
            break;
    
    int j = pos;
    for(; j < length; ++j)
        if(s[j] == ' ')
            break;
    if(s[i] != ' ')
        return j;
    if(s[j] != ' ')
        return i;

    return (pos - i) > (j - pos) ? j : i;
}
void SearchWord::Render(App* app)
{
    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(viewScreen)
        {
            delete viewScreen;
            viewScreen = nullptr;
        }
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
                delete word;
                word = nullptr;
                list = new WordList(app->dict->searchWord(searchbox->input));
                mode = Mode::SEARCH;
            }
            if(mode == Mode::SEARCH && !searchbox->startSearch && list)
            {
                list->Draw();
                word = list->getWord();
                if(word)
                    mode = Mode::VIEW;
            }
        }
        else
        {
            if(mode == Mode::SEARCH && list)
            {
                list->Draw();
                word = list->getWord();
                if(word)
                    mode = Mode::VIEW;
            }
        }

        if(defButton->isPressed())
            app->setNextScreen(new SearchDef());
    }
    else if(mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
}
SearchWord::SearchWord()
: mode(Mode::NOTSEARCH), word(nullptr), list(nullptr), viewScreen(nullptr)
{
    constexpr Vector2 origin = {50, 80};
    constexpr Vector2 size = {1100, 100};
    searchbox = new SearchBox(origin, size, GRAY);
    defButton = new search_by_def_button({origin.x, origin.y + size.y + 20}, {200, 75}, GRAY);

    wordButton = new search_by_word_button({origin.x - 10, defButton->origin.y + defButton->size.y + 15 - 5}, {220, 95}, GRAY);

    historyButton = new history_button({origin.x, wordButton->origin.y + wordButton->size.y + 15}, {200, 75}, GRAY);

    favoriteButton = new favorite_button({origin.x, historyButton->origin.y + historyButton->size.y + 15}, {200, 75}, GRAY);

    gamesButton = new games_button({origin.x, favoriteButton->origin.y + favoriteButton->size.y + 15}, {200, 75}, GRAY);

    resetButton = new reset_button({origin.x, gamesButton->origin.y + gamesButton->size.y + 15}, {200, 75}, GRAY);
    // cout << gamesButton->origin.y + gamesButton->size.y + 90 << "\n";

    constexpr Vector2 mode_origin = {50, 30};
    constexpr Vector2 mode_size = {200, 45};
    modesButtons = new modes_buttons(mode_origin, mode_size, WHITE);
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
    delete viewScreen;
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
    constexpr Vector2 origin = {50, 80};
    constexpr Vector2 size = {1100, 100};
    searchbox = new SearchBox(origin, size, GRAY);
    defButton = new search_by_def_button({origin.x - 10, origin.y + size.y + 20}, {220, 95}, GRAY);

    wordButton = new search_by_word_button({origin.x, defButton->origin.y + defButton->size.y + 10}, {200, 75}, GRAY);

    historyButton = new history_button({origin.x, wordButton->origin.y + wordButton->size.y + 15}, {200, 75}, GRAY);

    favoriteButton = new favorite_button({origin.x, historyButton->origin.y + historyButton->size.y + 15}, {200, 75}, GRAY);

    gamesButton = new games_button({origin.x, favoriteButton->origin.y + favoriteButton->size.y + 15}, {200, 75}, GRAY);

    resetButton = new reset_button({origin.x, gamesButton->origin.y + gamesButton->size.y + 15}, {200, 75}, GRAY);
    // cout << gamesButton->origin.y + gamesButton->size.y + 90 << "\n";

    constexpr Vector2 mode_origin = {50, 30};
    constexpr Vector2 mode_size = {200, 45};
    modesButtons = new modes_buttons(mode_origin, mode_size, WHITE);
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
    dict->loadData(ENGENG);
    SetTargetFPS(60);
    InitWindow(1200, 800, "DICTIONARY");
    currentScreen = new SearchWord();
    
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
    ClearBackground(RAYWHITE);
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