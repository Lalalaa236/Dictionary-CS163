#include "App.h"

State::State()
: change(false), dataset(ENGENG)
{}

ViewWord::ViewWord(WordButton* word, Screen* screen, App* app)
: word(word), screen(screen), app(app), showable(), origin({150, 180}), mode(0)
{
    SetShowable();
    backButton = new ReturnButton(app->asset, {1050, 112}, {45, 45}, RAYWHITE);
    favButton = new FavButton(app->asset, {1050, 652}, {45, 45}, word->data);
    removeButton = new remove_button(app->asset, {105, 654},{130,40}, {255,194,205,255}, BLACK, "REMOVE", 24);
    editbutton = new EditButton(app->asset, {1000, 652}, {45, 45}, RAYWHITE);
    viewdef = nullptr;
}

ViewWord::~ViewWord()
{
    delete backButton;
    delete favButton;
    delete removeButton;
}

AddWord::AddWord(App* app)
{
    this->app = app;
    addwordScreen = new AddWordScreen(this->app->asset);


}

AddWord::~AddWord()
{
    delete addwordScreen;
}

void ViewWord::Render(App* app, Screen* screen)
{
    if(mode == Mode::VIEW)
    {
        if(viewdef)
        {
            delete viewdef;
            viewdef = nullptr;
            SetShowable();
            word->createShowable();
        }
        DrawRectangleRec({100, 650, 1000, 50}, {255,194,205,255});
        DrawRectangle(100, 100, 1000, 70, {252,52,104,255});

        DrawRectangleLinesEx({100, 100, 1000, 600}, 5, BLACK);
        
        DrawLineEx({100, 650}, {1100, 650}, 5, BLACK);
        
        DrawTextEx(app->asset->font50, word->data->data.c_str(), {120, 120}, 45, 0, BLACK);

        removeButton->Draw();
        //DrawText(word->data->data.c_str(), 120, 120, 45, BLACK);
        Update();
    }
    else if(mode == Mode::EDIT)
    {
        viewdef->Render();
    }   
}

void ViewWord::Update()
{
    BeginScissorMode(150, 170, 1000, 480);
    //DrawText(showable.c_str(), this->origin.x, this->origin.y, 30, BLACK);
    DrawTextEx(app->asset->font30, showable.c_str(), {this->origin.x, this->origin.y}, 30, 0, BLACK);
    float offset = GetMouseWheelMove() * 30;
    if(MeasureTextEx(GetFontDefault(), showable.c_str(), 30, 0).y > 480)
    {
        if(this->origin.y + offset >= 180 && offset > 0)
            this->origin.y = 180;
        else if(this->origin.y + offset <= (700 - MeasureTextEx(app->asset->font30, showable.c_str(), 30, 0).y) && offset < 0)
            this->origin.y = 700 - MeasureTextEx(app->asset->font30, showable.c_str(), 30, 0).y;
        else
            this->origin.y += offset;
    }
    // cout << this->origin.y << "\n";
    EndScissorMode();
    if(backButton->Update())
        this->screen->mode = this->screen->Mode::SEARCH;

    if(word->data->favourite)
    {
        if(!favButton->Update(word->data))
        {
            this->app->dict->removeFromFavList(word->data, this->app->state.dataset);
            word->cur = app->asset->base; //marking
        }
    }
    else
    {
        if(favButton->Update(word->data))
        {
            this->app->dict->addToFavList(word->data, this->app->state.dataset);
            // cout << "welp";
            word->cur = app->asset->faved;
        }
    }

    if (removeButton->isPressed(false))
    {
        this->app->dict->removeWord(this->word->data->data,this->app->state.dataset);
        app->dict->deleteDict();
        app->dict->loadData(this->app->state.dataset);
        this->app->setNextScreen(new SearchWord(this->app));
    }

    if(editbutton->Update())
    {
        this->mode = Mode::EDIT;
        viewdef = new ViewDef(this);
    }
}

ViewDef::ViewDef(ViewWord* originalScreen)
: originalScreen(originalScreen), mode(0)
{
    asset = originalScreen->app->asset;
    word = originalScreen->word->data;
    backButton = new ReturnButton(originalScreen->app->asset, {1050, 112}, {45, 45}, RAYWHITE);
    origin = {120, 180};
    deflist = new DefList(originalScreen->app->asset, word->defs, word, origin);
    editscreen = nullptr;
}

void ViewDef::Render()
{
    if(mode == Mode::VIEW)
    {
        if(editscreen)
        {
            delete editscreen;
            editscreen = nullptr;
        }
        deflist->Draw();
        DrawRectangleRec({100, 650, 1000, 50}, {255,194,205,255});
        DrawRectangle(100, 100, 1000, 70, {252,52,104,255});

        DrawRectangleLinesEx({100, 100, 1000, 600}, 5, BLACK);
        
        DrawLineEx({100, 650}, {1100, 650}, 5, BLACK);
        
        DrawTextEx(asset->font50, word->data.c_str(), {120, 120}, 45, 0, BLACK);
        backButton->Draw();
        
        if(backButton->isPressed(false))
            originalScreen->mode = originalScreen->Mode::VIEW;
        EditDefButton* chosen = deflist->getDef();
        if(chosen)
        {
            mode = Mode::EDIT;
            editscreen = new EditDefScreen(asset, chosen, this);
        }
    }
    else if(mode == Mode::EDIT)
    {
        editscreen->Draw();//editscreen->buffer_def, editscreen->bufflen_def);
        editscreen->Update();
    }
    
}

ViewDef::~ViewDef()
{
    delete backButton;
    delete deflist;
    delete editscreen;
}

void AddWord::Render(App* app)
{
    addwordScreen->Draw(addwordScreen->buffer, addwordScreen->bufflen,addwordScreen->buffer_def, addwordScreen->bufflen_def,addwordScreen->buffer_type, addwordScreen->bufflen_type);
    addwordScreen->Save(this->app->dict,this->app->state.dataset);
    if(addwordScreen->startAdd)
        app->setNextScreen(new SearchWord(this->app));
}

void ViewWord::SetShowable()
{
    showable.clear();
    int size = word->data->defs.size();
    for(int i = 0; i < size; ++i)
    {
        string cpy = word->data->defs[i]->data;
        int length = cpy.length();
        int start = 0;
        string tmp;
        for(int j = 0; j < length; ++j)
        {
            if(MeasureTextEx(app->asset->font30, tmp.c_str(), 30, 0).x > 830)
            {
                tmp.clear();
                int k = j;
                while(k >= j - 50)
                {
                    if(cpy[k] == ' ' || cpy[k] == '\n')
                        break;
                    --k;
                }
                if(k < j - 50)
                {
                    cpy.insert(j, "-");
                    cpy.insert(j + 1, "\n");
                    length += 2;
                    j += 2;
                }
                else if(cpy[k] == ' ')
                {
                    cpy[k] = '\n';
                    j = k;
                    start = j;
                }      
            }
            else
                tmp.push_back(cpy[j]);
            //cout << count << "!\n";
        }
        showable.append(cpy);
        showable.append("\n\n");
    }
    // cout << showable;
}

int ViewWord::findNearestSpace(const string& s, int length, int pos)
{
    int i = pos;
    for(; i >= 0; --i)
        if(s[i] == ' ')
            break;
    
    // int j = pos;
    // for(; j < length; ++j)
    //     if(s[j] == ' ')
    //         break;
    // if(s[i] != ' ')
    //     return j;
    // if(s[j] != ' ')
    //     return i;

    // return (pos - i) > (j - pos) ? j : i;

    return i;
}

// Word* ViewWord::getWord()
// {
//     return word;
// }
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
        
        //cout << "fuck\n";

        defButton->Draw();

        wordButton->Draw();

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(historyButton->isPressed(false)) {
            app->setNextScreen(new HistoryScreen(this->app));
        }

        if(favoriteButton->isPressed(false)) {
            app->setNextScreen(new FavoriteScreen(this->app));
        }

        if(gamesButton->isPressed(false)) {
            app->setNextScreen(new GameScreen(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        if(shuffleButton->Update()) 
        {
            delete list;
            list = nullptr;
            list = new WordList(app->asset, app->dict->randomWord());
            mode = Mode::SEARCH;
            if(mode == Mode::SEARCH && list)
            {
                list->Draw(modesButtons->isDropdown);
                word = list->getWord(modesButtons->after_change);
                if(word)
                {
                    this->mode = Mode::VIEW;
                }
            }
        }

        if(!searchbox->state)
        {
            if (modesButtons->change_data)
            {
                searchbox->startSearch = true;
                modesButtons->change_data = false;
            }
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                // delete word;
                word = nullptr;
                list = new WordList(app->asset, app->dict->searchWord(searchbox->input));
                mode = Mode::SEARCH;
            }
            if(mode == Mode::SEARCH && !searchbox->startSearch && list)
            {
                list->Draw(modesButtons->isDropdown);
                word = list->getWord(modesButtons->after_change);
                if(word)
                {
                    this->mode = Mode::VIEW;
                    // this->app->dict->history.push_back(word->data);
                    this->app->dict->addToHis(word->data, this->app->state.dataset);
                }
            }
        }
        else
        {
            if(mode == Mode::SEARCH && list)
            {
                list->Draw(modesButtons->isDropdown);
                word = list->getWord(modesButtons->after_change);
                if(word)
                {
                    this->mode = Mode::VIEW;
                    // this->app->dict->history.push_back(word->data);
                    this->app->dict->addToHis(word->data, this->app->state.dataset);

                }
            }
        }

        if(defButton->isPressed(false))
            app->setNextScreen(new SearchDef(this->app));
      modesButtons->Draw(this->app->state.dataset,this->app->dict);
    }
    else if(mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
    // cout << mode << "\n";
}

SearchWord::SearchWord(App* app)
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {605, 70};
    Color btnColor = {255,98,137,255};

    searchbox = new SearchBox(app->asset, origin, size, {WHITE});

    shuffleButton = new ShuffleButton(app->asset, {origin.x + size.x + 5, 50}, {70, 70}, btnColor);

    wordButton = new search_by_word_button(this->app->asset, {30, origin.y }, {125, 70}, btnColor, WHITE,21);

    defButton = new search_by_def_button(this->app->asset, {30+wordButton->size.x, origin.y },  {125, 70}, WHITE,BLACK,21);

    addWordButton = new add_word_button(this->app->asset, {30, wordButton->origin.y + wordButton->size.y + searchbox->size.y - 10}, {250, 100},btnColor,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(this->app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},btnColor,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(this->app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},btnColor,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(this->app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},btnColor,"Game","Enhance your vocabulary",BLACK,24);

    resetButton = new reset_button(this->app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, btnColor,WHITE,24);
    
    constexpr Vector2 mode_origin = {origin.x+size.x + 95, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(this->app->asset, mode_origin, mode_size, WHITE,BLACK,25);
    //cout << "jesus christ!\n";
    Word* word;
    this->app->dict->trie.findWhole("set", word);
    //deflist = new DefList(this->app->asset, word->defs, word, {30, 50});
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
    //delete deflist;
}

void SearchDef::Render(App* app)
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

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        if(shuffleButton->Update()) 
        {
            delete list;
            list = nullptr;
            list = new WordList(app->asset, app->dict->randomWord());
            mode = Mode::SEARCH;
            if(mode == Mode::SEARCH && list)
            {
                list->Draw(modesButtons->isDropdown);
                word = list->getWord(modesButtons->after_change);
                if(word)
                {
                    this->mode = Mode::VIEW;
                }
            }
        }

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(historyButton->isPressed(false)) {
            app->setNextScreen(new HistoryScreen(this->app));
        }

        if(favoriteButton->isPressed(false)) {
            app->setNextScreen(new FavoriteScreen(this->app));
        }

        if(gamesButton->isPressed(false)) {
            app->setNextScreen(new GameScreen(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        if(!searchbox->state)
        {
            if (modesButtons->change_data)
            {
                searchbox->startSearch = true;
                modesButtons->change_data = false;
            }
            if(searchbox->startSearch)
            {
                delete list;
                list = nullptr;
                // delete word;
                word = nullptr;
                list = new WordList(app->asset, app->dict->searchDef(searchbox->input));
                mode = Mode::SEARCH;
            }
            if(mode == Mode::SEARCH && !searchbox->startSearch && list)
            {
                list->Draw(modesButtons->isDropdown);
                word = list->getWord(modesButtons->isDropdown);
                if(word)
                {
                    this->mode = Mode::VIEW;
                    // this->app->dict->history.push_back(word->data);
                    this->app->dict->addToHis(word->data, this->app->state.dataset);
                }
            }
        }
        else
        {
            if(mode == Mode::SEARCH && list)
            {
                list->Draw(modesButtons->isDropdown);
                word = list->getWord(modesButtons->isDropdown);
                if(word)
                {
                    this->mode = Mode::VIEW;
                    // this->app->dict->history.push_back(word->data);
                    this->app->dict->addToHis(word->data, this->app->state.dataset);
                }
            }
        }

        if(wordButton->isPressed(false))
            app->setNextScreen(new SearchWord(this->app));
        modesButtons->Draw(this->app->state.dataset,this->app->dict);

    }
    else if(mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
}

SearchDef::SearchDef(App* app)
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {605, 70};
    Color btnColor = {255,98,137,255};
    searchbox = new SearchBox(app->asset, origin, size, WHITE);

    shuffleButton = new ShuffleButton(app->asset, {origin.x + size.x + 5, 50}, {70, 70}, btnColor);

    wordButton = new search_by_word_button(app->asset, {30, origin.y },  {125, 70}, WHITE,BLACK,21);
    defButton = new search_by_def_button(app->asset, {30+wordButton->size.x, origin.y }, {125, 70}, btnColor, WHITE,21);

    addWordButton = new add_word_button(app->asset, {30, wordButton->origin.y + wordButton->size.y + searchbox->size.y - 10}, {250, 100},btnColor,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},btnColor,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},btnColor,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},btnColor,"Game","Enhance your vocabulary",BLACK,24);

    resetButton = new reset_button(app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, btnColor,WHITE,24);

    constexpr Vector2 mode_origin = {origin.x+size.x + 95, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(app->asset, mode_origin, mode_size, btnColor,BLACK,25);
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
    delete viewScreen;
}

App::App()
: mode(1), dict(new Dictionary())
{
    if(GetWindowHandle())
        return;
    dict->loadData(state.dataset);
    SetTargetFPS(60);
    InitWindow(1200, 800, "DICTIONARY");
    asset = new Asset();
    currentScreen = new SearchWord(this);
}

App::~App()
{
    if(!GetWindowHandle())
        return;
    CloseWindow();
    delete currentScreen;
    delete dict;
    delete asset;
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
    ClearBackground({255,235,250,100});
}

void App::Update()
{
    this->render(this->currentScreen);
}

void App::run()
{
    while(!this->AppShouldClose())
    {
        if(this->state.change)
        {
            this->state.change = false;
            dict->deleteDict();
            dict->loadData(this->state.dataset);
        }
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

void FavoriteScreen::Render(App* app)
{
    ClearBackground({255,235,250,100});
    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {

        if(viewScreen)
        {
            delete viewScreen;
            viewScreen = nullptr;
        }
        if(word)
            word = nullptr;

        defButton->Draw();
        wordButton->Draw();

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(historyButton->isPressed(false)) {
            app->setNextScreen(new HistoryScreen(this->app));
        }
        
        if(defButton->isPressed(false))
        {
            app->setNextScreen(new SearchDef(this->app));
        }

        if(wordButton->isPressed(false))
        {
            app->setNextScreen(new SearchWord(this->app));
        }

        if(gamesButton->isPressed(false)) {
            app->setNextScreen(new GameScreen(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        Vector2 _origin = {300, 50};
        Vector2 _size = {870, 70};
        DrawRectangle(_origin.x, _origin.y, _size.x - 20, _size.y, {255,98,137,255});
        // DrawText("  Favorite", _origin.x + 10, _origin.y + (_size.y - 36)/2, 48, WHITE);
        DrawTextEx(this->app->asset->font50,"   FAVORITE", {_origin.x + 10, _origin.y + (_size.y - 55)/2}, 55,3, WHITE);

        // backButton->Draw();
        // delete word;

        if (!list)
            list = new WordList(app->asset, app->dict->viewFavList(this->app->state.dataset));
    
        list->Draw(modesButtons->isDropdown);

        word = list->getWord(modesButtons->isDropdown);
        if(word)
        {
            this->mode = Mode::VIEW;
        }

        // if(backButton->Update())
        //     app->setNextScreen(new SearchDef);
    }
    if (mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
    
}

FavoriteScreen::FavoriteScreen(App* app)
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    // backButton = new ReturnButton({1050, 112}, {45, 45}, RAYWHITE);

    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {700, 70};
    Color btnColor = {255,98,137,255};

    wordButton = new search_by_word_button(app->asset, {30, origin.y },  {125, 70}, btnColor, WHITE,21);
    defButton = new search_by_def_button(app->asset, {30 + wordButton->size.x, origin.y }, {125, 70}, btnColor, WHITE,21);

    addWordButton = new add_word_button(app->asset, {30, wordButton->origin.y + wordButton->size.y + 60}, {250, 100},btnColor,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},btnColor,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},btnColor,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},btnColor,"Game","Enhance your vocabulary",BLACK,24);

    resetButton = new reset_button(app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, btnColor,WHITE,24);

    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(app->asset, mode_origin, mode_size, WHITE,BLACK,25);
}

FavoriteScreen::~FavoriteScreen()
{
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete list;
    delete viewScreen;
}


void HistoryScreen::Render(App* app)
{
    ClearBackground({255,235,250,100});

    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(viewScreen)
        {
            delete viewScreen;
            viewScreen = nullptr;
        }
        if(word)
            word = nullptr;

        defButton->Draw();
        wordButton->Draw();

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(favoriteButton->isPressed(false)) {
            app->setNextScreen(new FavoriteScreen(this->app));
        }
        
        if(defButton->isPressed(false))
        {
            app->setNextScreen(new SearchDef(this->app));
        }

        if(wordButton->isPressed(false))
        {
            app->setNextScreen(new SearchWord(this->app));
        }

        if(gamesButton->isPressed(false)) {
            app->setNextScreen(new GameScreen(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        Vector2 _origin = {300, 50};
        Vector2 _size = {870, 70};
        ClearBackground(RAYWHITE);
        DrawRectangle(_origin.x, _origin.y, _size.x - 20, _size.y, PINK);
        // DrawText("  Favorite", _origin.x + 10, _origin.y + (_size.y - 36)/2, 48, WHITE);
        DrawTextEx(this->app->asset->font50,"   HISTORY", {_origin.x + 10, _origin.y + (_size.y - 55)/2}, 55,3, WHITE);

        // backButton->Draw();  
        // delete word;

        if (!list)
            list = new WordList(app->asset, app->dict->getHis(this->app->state.dataset));
            // std::cout << "fuck";
    
        list->Draw(modesButtons->isDropdown);

        word = list->getWord(modesButtons->isDropdown);
        if(word)
        {
            this->mode = Mode::VIEW;
        }

        // if(backButton->Update())
        //     app->setNextScreen(new SearchDef);
    }
    if (mode == Mode::VIEW)
    {
        if(!viewScreen)
            viewScreen = new ViewWord(word, this, app);
        viewScreen->Render(app, this);
    }
    
}

HistoryScreen::HistoryScreen(App* app)
: word(nullptr), list(nullptr), viewScreen(nullptr)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    // backButton = new ReturnButton({1050, 112}, {45, 45}, RAYWHITE);

    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {700, 70};
    Color btnColor = {255,98,137,255};

    wordButton = new search_by_word_button(app->asset, {30, origin.y },  {125, 70}, btnColor, WHITE,21);
    defButton = new search_by_def_button(app->asset, {30 + wordButton->size.x, origin.y }, {125, 70}, btnColor, WHITE,21);

    addWordButton = new add_word_button(app->asset, {30, wordButton->origin.y + wordButton->size.y + 60}, {250, 100},btnColor,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},btnColor,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},btnColor,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},btnColor,"Game","Enhance your vocabulary",BLACK,24);

    resetButton = new reset_button(app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, btnColor,WHITE,24);

    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(app->asset, mode_origin, mode_size, WHITE,BLACK,25);
    // cout << "ah\n";
    // his = app->dict->getHis();

}

HistoryScreen::~HistoryScreen()
{
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete list;
    delete viewScreen;
}

// void HistoryScreen::Render(App* app)
// {
//     Vector2 _origin = {50, 80};
//     Vector2 _size = {1100, 100};
//     ClearBackground(RAYWHITE);
//     DrawRectangle(_origin.x, _origin.y, _size.x, _size.y, BLUE);
//     DrawText("History", _origin.x + 10, _origin.y + (_size.y - 36)/2, 48, LIGHTGRAY);
//     Vector2 return_origin = {50, 10};
//     Vector2 return_size = {100, 50};
//     DrawRectangle(return_origin.x, return_origin.y, return_size.x, return_size.y, RED);
// }



// HistoryScreen::HistoryScreen(App* app)
// {
//     this->app = app;
// }

void ResetWarning::Render(App* app)
{
    Vector2 _origin = {300, 250};
    Vector2 _size = {600, 200};
    ClearBackground({255,235,250,100});
    DrawRectangle(_origin.x, _origin.y, _size.x, _size.y, WHITE);
    DrawText("Are you sure you want to reset?", _origin.x + 40, _origin.y + 30, 30, {255,8,74,255});
    // DrawRectangle(_origin.x + 140, _origin.y + 140, 120, 40, WHITE);
    // DrawRectangleLinesEx({_origin.x + 140, _origin.y + 140, 120, 40}, 3, BLACK);
    // DrawText("YES", _origin.x + 178, _origin.y + 153, 20, BLACK);
    // DrawRectangle(_origin.x + 340, _origin.y + 140, 120, 40, WHITE);
    // DrawRectangleLinesEx({_origin.x + 340, _origin.y + 140, 120, 40}, 3, BLACK);
    // DrawText("NO", _origin.x + 382, _origin.y + 153, 20, BLACK);
    YesBtn->Draw();
    NoBtn->Draw();

    if (NoBtn->isPressed(false))
    {
        app->setNextScreen(new SearchWord(this->app));
    }
    if (YesBtn->isPressed(false))
    {
        app->dict->resetDictionary();
        app->dict->deleteDict();
        app->dict->loadData(app->state.dataset);
        app->setNextScreen(new SearchWord(this->app));
    }
}

ResetWarning::ResetWarning(App* app)
{
    Vector2 origin = {300, 250};
    Vector2 size = {600, 200};
    Color noBtnColor = {255,98,137,255};
    Color yesBtnColor = {255,98,137,255};

    this->app = app;
    YesBtn = new YesNo_button(app->asset, {origin.x + 140, origin.y + 140}, {120, 40}, yesBtnColor, WHITE,"   YES", 24);
    NoBtn = new YesNo_button(app->asset, {origin.x + 340, origin.y + 140}, {120, 40}, noBtnColor, WHITE,"   NO", 24);
}

ResetWarning::~ResetWarning()
{
    delete YesBtn;
    delete NoBtn;
}

void EditDefScreen::CursorBlink(float time) //blinking cursor 
{
    cursorBlinkTime += time;
    if (cursorBlinkTime >= 1.0f)
        cursorBlinkTime = 0.0f;
}

void EditDefScreen::Draw()
{
    Vector2 origin = {120,180};
    // DrawRectangle(30,50,1100,650,WHITE);
    DrawRectangleRec({100, 650, 1000, 50}, {255,194,205,255});
    DrawRectangle(100, 100, 1000, 70, {252,52,104,255});
    DrawRectangleLinesEx({100, 100, 1000, 600}, 5, BLACK);
    DrawLineEx({100, 650}, {1100, 650}, 5, BLACK);

    // DrawLine(origin.x,origin.y,500,origin.y,BLACK);
    
    DrawTextEx(asset->font50, word->data.c_str(),{origin.x,origin.y-60}, 45, 0,BLACK);
    DrawTextEx(asset->font30, showable.c_str(), {origin.x,origin.y+20}, 30, 0,BLACK);

    // DrawRectangleRec({100, 650, 1000, 50}, {255,194,205,255});
    // DrawRectangle(100, 100, 1000, 70, {252,52,104,255});

    // DrawRectangleLinesEx({100, 100, 1000, 600}, 5, BLACK);
    
    // DrawLineEx({100, 650}, {1100, 650}, 5, BLACK);
    
    // DrawTextEx(app->asset->font50, word->data->data.c_str(), {120, 120}, 45, 0, BLACK);

    savebutton->Draw();
    if(bufflen_def == 0 && is_enter_def == false)
        DrawTextEx(asset->font50, "Add the definition here",{origin.x,origin.y+70}, 38, 0,  {155,155,155,255});
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {   
        if(CheckCollisionPointRec(GetMousePosition(), def_rec))
            is_enter_def = true;  
        else if(is_enter_def)
            is_enter_def = false; 
    }
    if (is_enter_def)
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        if((key >= 32) && (key <= 125) && input_def.length() < 700)
        {
            input_def.push_back(key);
            SetShowable();
        }

        key = GetCharPressed();

        if(IsKeyPressed(KEY_BACKSPACE))
        {
            
            if(input_def.length() > 0)
            {
                input_def.pop_back();
                SetShowable();
            }
                
        }

        key = GetCharPressed();

        if(IsKeyPressed(KEY_ENTER))
            is_enter_def = false;
        CursorBlink(GetFrameTime());
    }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void EditDefScreen::SetShowable()
{
    showable.clear();
    showable = input_def;
    int start = 0;
    int length = showable.length();
    string tmp;
    for(int i = 0; i < length; ++i)
    {
        if(MeasureTextEx(asset->font30, tmp.c_str(), 30, 0).x > 980)
        {
            tmp.clear();
            int k = i;
            while(k >= i - 50)
            {
                if(showable[k] == ' ' || showable[k] == '\n')
                    break;
                --k;
            }

            if(k < i - 50)
            {
                showable.insert(i, "-");
                showable.insert(i + 1, "\n");
                length += 2;
                i += 2;
            }
            else if(showable[k] == ' ')
            {
                showable[k] = '\n';
                i = k;
                start = i;
            }      
        }

        else
            tmp.push_back(showable[i]);
    }
}

void EditDefScreen::Update()
{
    if(savebutton->isPressed(false))
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        int count = 0;
        while(input_def[count] == ' ')
        {
            ++count;
        }
        input_def = input_def.substr(count, input_def.length() - count);
        if(input_def.empty() || input_def[0] != '(')
            input_def.insert(0, "()");
        string oldstring = word->data + " " + def->data;
        def->data = input_def;
        string newstring = word->data + " " + def->data;
        viewdef->originalScreen->app->dict->editDef(viewdef->originalScreen->app->state.dataset, newstring, oldstring);
        for(int i = 0; i < viewdef->deflist->defs.size(); ++i)
        {
            if(viewdef->deflist->defs[i] == chosen)
            {
                Vector2 pos = chosen->origin;
                Color color = chosen->rectangleColor;
                delete chosen;
                chosen = new EditDefButton(asset, def, pos, color);
                viewdef->deflist->defs[i] = chosen;
                break;
            }
        }
        viewdef->mode = viewdef->Mode::VIEW;
    }
}

EditDefScreen::~EditDefScreen()
{
    delete savebutton;
}

void GameScreen::Render(App* app)
{
    ClearBackground({255,235,250,100});

    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(viewScreen)
        {
            delete viewScreen;
            viewScreen = nullptr;
        }
        if(word)
            word = nullptr;

        defButton->Draw();
        wordButton->Draw();

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        guessDefBtn->Draw();

        guessWordBtn->Draw();

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(historyButton->isPressed(false)) {
            app->setNextScreen(new HistoryScreen(this->app));
        }

        if(favoriteButton->isPressed(false)) {
            app->setNextScreen(new FavoriteScreen(this->app));
        }
        
        if(defButton->isPressed(false))
        {
            app->setNextScreen(new SearchDef(this->app));
        }

        if(wordButton->isPressed(false))
        {
            app->setNextScreen(new SearchWord(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        if(guessDefBtn->isPressed(false)) {
            app->setNextScreen(new GuessDefScreen(this->app));
        }

        if(guessWordBtn->isPressed(false)) {
            app->setNextScreen(new GuessWordScreen(this->app));
        }

        Vector2 _origin = {300, 50};
        Vector2 _size = {870, 70};
        DrawRectangle(_origin.x, _origin.y, _size.x - 20, _size.y, {255,98,137,255});
        DrawTextEx(this->app->asset->font50,"   GAME", {_origin.x + 10, _origin.y + (_size.y - 55)/2}, 55,3, WHITE);

        DrawRectangle(_origin.x, _origin.y + 250, _size.x + 150, _size.y, {255,98,137,255});
        DrawTextEx(this->app->asset->font50,"  WHAT GAME DO YOU WANT TO PLAY?", {_origin.x + 170, _origin.y + (_size.y - 30)/2 + 250}, 30,3, WHITE);
    }
    
}

GameScreen::GameScreen(App* app)
: word(nullptr), viewScreen(nullptr)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    // backButton = new ReturnButton({1050, 112}, {45, 45}, RAYWHITE);

    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {700, 70};
    Color btnColor = {255,98,137,255};

    wordButton = new search_by_word_button(app->asset, {30, origin.y },  {125, 70}, btnColor, WHITE,21);
    defButton = new search_by_def_button(app->asset, {30 + wordButton->size.x, origin.y }, {125, 70}, btnColor, WHITE,21);

    addWordButton = new add_word_button(app->asset, {30, wordButton->origin.y + wordButton->size.y + 60}, {250, 100},btnColor,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},btnColor,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},btnColor,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},btnColor,"Game","Enhance your vocabulary",BLACK,24);

    resetButton = new reset_button(app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, btnColor,WHITE,24);

    guessDefBtn = new Guess_button(app->asset, {origin.x + 50, origin.y + 350}, {300, 70}, btnColor, WHITE, "   Guess Definition", 30);
    guessWordBtn = new Guess_button(app->asset, {origin.x + 500, origin.y + 350}, {300, 70}, btnColor, WHITE, "       Guess Word", 30);

    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(app->asset, mode_origin, mode_size, WHITE,BLACK,25);
    // cout << "ah\n";
    // his = app->dict->getHis();
}

GameScreen::~GameScreen()
{
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete viewScreen;
}


void GuessDefScreen::Render(App* app)
{
    ClearBackground({255,235,250,100});

    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(viewScreen)
        {
            delete viewScreen;
            viewScreen = nullptr;
        }
        if(word)
            word = nullptr;

        defButton->Draw();
        wordButton->Draw();

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        // guessDefBtn->Draw();

        // guessWordBtn->Draw();

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(historyButton->isPressed(false)) {
            app->setNextScreen(new HistoryScreen(this->app));
        }

        if(favoriteButton->isPressed(false)) {
            app->setNextScreen(new FavoriteScreen(this->app));
        }
        
        if(defButton->isPressed(false))
        {
            app->setNextScreen(new SearchDef(this->app));
        }

        if(wordButton->isPressed(false))
        {
            app->setNextScreen(new SearchWord(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        if(gamesButton->isPressed(false)) {
            app->setNextScreen(new GameScreen(this->app));
        }

        Vector2 _origin = {300, 50};
        Vector2 _size = {700, 70};
        DrawRectangle(_origin.x, _origin.y, _size.x - 20, _size.y, {255,98,137,255});
        DrawTextEx(this->app->asset->font50,"   GUESS DEFINITION", {_origin.x + 10, _origin.y + (_size.y - 55)/2}, 55,3, WHITE);

        if (!gameWord)
        {
            delete gameWord;
            multi_choices.clear();
            this->app->dict->guessDef(gameWord, def_ans, pos_ans, multi_choices);
            modeGame = ModeGame::START;

            if (modeGame == ModeGame::START && gameWord)
            {
                DrawRectangle(_origin.x, _origin.y + 130, _size.x + 150, _size.y, {255,98,137,255});
                string t = "    What is the definition of " + gameWord->data + "?";
                DrawTextEx(this->app->asset->font50,t.c_str(), {_origin.x + 10, _origin.y + (_size.y - 35)/2 + 130}, 55,3, WHITE);
                // cout << "1." << multi_choices[0] << '\n';
                firstChoice->DrawChoice(multi_choices[0]);
                // cout << "2."<< multi_choices[1] << '\n';
                secondChoice->DrawChoice(multi_choices[1]);
                // cout << "3."<< multi_choices[2] << '\n';
                thirdChoice->DrawChoice(multi_choices[2]);
                // cout << "4."<< multi_choices[3] << '\n';
                fourthChoice->DrawChoice(multi_choices[3]);
            }
        }

        if (modeGame == ModeGame::START && gameWord)
        {
            DrawRectangle(_origin.x, _origin.y + 130, _size.x + 150, _size.y, {255,98,137,255});
            string t = "What is the definition of " + gameWord->data + "?";
            DrawTextEx(this->app->asset->font50,t.c_str(), {_origin.x + 10, _origin.y + (_size.y - 35)/2 + 130}, 30,3, WHITE);
            firstChoice->DrawChoice(multi_choices[0]);
            secondChoice->DrawChoice(multi_choices[1]);
            thirdChoice->DrawChoice(multi_choices[2]);
            fourthChoice->DrawChoice(multi_choices[3]);

            if (firstChoice->isPressed(false))
            {
                if (pos_ans == 0)
                    modeGame = ModeGame::RIGHT;
                else    
                    modeGame = ModeGame::WRONG;
            }
            if (secondChoice->isPressed(false))
            {
                if (pos_ans == 1)
                    modeGame = ModeGame::RIGHT;
                else    
                    modeGame = ModeGame::WRONG;
            }
            if (thirdChoice->isPressed(false))
            {
                if (pos_ans == 2)
                    modeGame = ModeGame::RIGHT;
                else    
                    modeGame = ModeGame::WRONG;
            }
            if (fourthChoice->isPressed(false))
            {
                if (pos_ans == 3)
                    modeGame = ModeGame::RIGHT;
                else    
                    modeGame = ModeGame::WRONG;
            }
        }

        if (modeGame == ModeGame::RIGHT)
        {
            DrawRectangle(_origin.x, _origin.y + 250, _size.x + 150, _size.y, {255,98,137,255});
            DrawTextEx(this->app->asset->font50,"CONGRATULATION! YOU ARE RIGHT", {_origin.x + 220, _origin.y + (_size.y - 30)/2 + 250}, 30,3, WHITE);
            
            counter++;

            if (counter > 25)
            {
                counter = 101;
                yesBtn->Draw();
                noBtn->Draw();
                if (yesBtn->isPressed(false))
                {
                    this->app->setNextScreen(new GuessDefScreen(this->app));
                }
                if (noBtn->isPressed(false))
                {
                    this->app->setNextScreen(new GameScreen(this->app));
                }
            }
        }
        if (modeGame == ModeGame::WRONG)
        {
            DrawRectangle(_origin.x, _origin.y + 250, _size.x + 150, _size.y, {255,98,137,255});
            DrawTextEx(this->app->asset->font50,"YOU CHOSE A WRONG ANSWER", {_origin.x + 225, _origin.y + (_size.y - 30)/2 + 250}, 30,3, WHITE);
            
            counter++;

            if (counter > 25)
            {
                counter = 101;
                yesBtn->Draw();
                noBtn->Draw();
                if (yesBtn->isPressed(false))
                {
                    this->app->setNextScreen(new GuessDefScreen(this->app));
                }
                if (noBtn->isPressed(false))
                {
                    this->app->setNextScreen(new GameScreen(this->app));
                }
            }
        }
    }
}

GuessDefScreen::GuessDefScreen(App* app)
: word(nullptr), viewScreen(nullptr), gameWord(nullptr), counter(0)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    this->modeGame = ModeGame::PREPARE;
    // backButton = new ReturnButton({1050, 112}, {45, 45}, RAYWHITE);

    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {700, 70};
    Color btnColor = {255,98,137,255};

    wordButton = new search_by_word_button(app->asset, {30, origin.y },  {125, 70}, btnColor, WHITE,21);
    defButton = new search_by_def_button(app->asset, {30 + wordButton->size.x, origin.y }, {125, 70}, btnColor, WHITE,21);

    addWordButton = new add_word_button(app->asset, {30, wordButton->origin.y + wordButton->size.y + 60}, {250, 100},btnColor,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},btnColor,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},btnColor,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},btnColor,"Game","Enhance your vocabulary",BLACK,24);

    resetButton = new reset_button(app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, btnColor,WHITE,24);

    yesBtn = new YesNo_button(app->asset, {origin.x + 50, origin.y + 350}, {300, 70}, btnColor, WHITE, "          Continue", 30);
    noBtn = new YesNo_button(app->asset, {origin.x + 500, origin.y + 350}, {300, 70}, btnColor, WHITE, "             Leave", 30);

    firstChoice = new Choices_button(app->asset, {origin.x, origin.y + 240}, {850, 100}, btnColor, WHITE, 23);
    secondChoice = new Choices_button(app->asset, {origin.x, firstChoice->origin.y + firstChoice->size.y + 10}, {850, 100}, btnColor, WHITE, 23);
    thirdChoice = new Choices_button(app->asset, {origin.x, secondChoice->origin.y + secondChoice->size.y + 10}, {850, 100}, btnColor, WHITE, 23);
    fourthChoice = new Choices_button(app->asset, {origin.x, thirdChoice->origin.y + thirdChoice->size.y + 10}, {850, 100}, btnColor, WHITE, 23);

    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(app->asset, mode_origin, mode_size, WHITE,BLACK,25);
}

GuessDefScreen::~GuessDefScreen()
{
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete viewScreen;
}

void GuessWordScreen::Render(App* app)
{
    ClearBackground({255,235,250,100});

    if(mode == Mode::SEARCH || mode == Mode::NOTSEARCH)
    {
        if(viewScreen)
        {
            delete viewScreen;
            viewScreen = nullptr;
        }
        if(word)
            word = nullptr;

        defButton->Draw();
        wordButton->Draw();

        addWordButton->Draw();

        historyButton->Draw();

        favoriteButton->Draw();

        gamesButton->Draw();

        resetButton->Draw();

        if(addWordButton->isPressed(false)) {
            app->setNextScreen(new AddWord(this->app));
        }

        if(historyButton->isPressed(false)) {
            app->setNextScreen(new HistoryScreen(this->app));
        }

        if(favoriteButton->isPressed(false)) {
            app->setNextScreen(new FavoriteScreen(this->app));
        }
        
        if(defButton->isPressed(false))
        {
            app->setNextScreen(new SearchDef(this->app));
        }

        if(wordButton->isPressed(false))
        {
            app->setNextScreen(new SearchWord(this->app));
        }

        if(resetButton->isPressed(false)) {
            app->setNextScreen(new ResetWarning(this->app));
        }

        if(gamesButton->isPressed(false)) {
            app->setNextScreen(new GameScreen(this->app));
        }

        Vector2 _origin = {300, 50};
        Vector2 _size = {700, 70};
        DrawRectangle(_origin.x, _origin.y, _size.x - 20, _size.y, {255,98,137,255});
        DrawTextEx(this->app->asset->font50,"   GUESS WORD", {_origin.x + 10, _origin.y + (_size.y - 55)/2}, 55,3, WHITE);

        if (!gameDef)
        {
            delete gameDef;
            multi_choices.clear();
            this->app->dict->chooseWord(gameDef, def_ans, pos_ans, multi_choices);
            modeGame = ModeGame::START;

            if (modeGame == ModeGame::START && gameDef)
            {
                DrawRectangle(_origin.x, _origin.y + 130, _size.x + 150, _size.y, {255,98,137,255});
                string t = "    What is the word of \"" + gameDef->data + "\"?";
                cout << gameDef->data;
                DrawTextEx(this->app->asset->font50,t.c_str(), {_origin.x + 10, _origin.y + (_size.y - 35)/2 + 130}, 20,3, WHITE);
                // cout << "1." << multi_choices[0] << '\n';
                firstChoice->Draw(multi_choices[0]);
                // cout << "2."<< multi_choices[1] << '\n';
                secondChoice->Draw(multi_choices[1]);
                // cout << "3."<< multi_choices[2] << '\n';
                thirdChoice->Draw(multi_choices[2]);
                // cout << "4."<< multi_choices[3] << '\n';
                fourthChoice->Draw(multi_choices[3]);
            }
        }

        if (modeGame == ModeGame::START && gameDef)
        {
            string t = "      What is the definition of \"" + gameDef->data + "\"?";

            int down = 0;

            int i = 84;
            if (t.length() > 85)
            {
                while(t[i] != ' ')
                    i--;
                if (i < t.length())
                {
                    t.insert(i, "\n");
                    down++;
                }
                i = 154;
                if (t.length() > 155)
                {
                    while(t[i] != ' ')
                        i--;
                    if (i < t.length())
                    {
                        t.insert(i, "\n");
                        down++;
                    }
                    i = 234;
                    if (t.length() > 235)
                    {
                        while(t[i] != ' ')
                            i--;
                        if (i < t.length())
                        {
                            t.insert(i, "\n");
                            down++;
                        }
                        i = 314;
                        if (t.length() > 315)
                        {
                            while(t[i] != ' ')
                                i--;
                            if (i < t.length())
                            {
                                t.insert(i, "\n");
                                down++;
                            }
                        }
                    }
                }
            }

            DrawRectangle(_origin.x, _origin.y + 130, _size.x + 150, _size.y + 30 * down, {255,98,137,255});
            DrawTextEx(this->app->asset->font50,t.c_str(), {_origin.x + 10, _origin.y + (_size.y - 14 - 10 * down)/2 + 130}, 25,1, WHITE);
            firstChoice->Draw(multi_choices[0]);
            secondChoice->Draw(multi_choices[1]);
            thirdChoice->Draw(multi_choices[2]);
            fourthChoice->Draw(multi_choices[3]);

            if (firstChoice->isPressed(false))
            {
                if (pos_ans == 0)
                    modeGame = ModeGame::RIGHT;
                else    
                    modeGame = ModeGame::WRONG;
            }
            if (secondChoice->isPressed(false))
            {
                if (pos_ans == 1)
                    modeGame = ModeGame::RIGHT;
                else    
                    modeGame = ModeGame::WRONG;
            }
            if (thirdChoice->isPressed(false))
            {
                if (pos_ans == 2)
                    modeGame = ModeGame::RIGHT;
                else    
                    modeGame = ModeGame::WRONG;
            }
            if (fourthChoice->isPressed(false))
            {
                if (pos_ans == 3)
                    modeGame = ModeGame::RIGHT;
                else    
                    modeGame = ModeGame::WRONG;
            }
        }

        if (modeGame == ModeGame::RIGHT)
        {
            DrawRectangle(_origin.x, _origin.y + 250, _size.x + 150, _size.y, {255,98,137,255});
            DrawTextEx(this->app->asset->font50,"CONGRATULATION! YOU ARE RIGHT", {_origin.x + 220, _origin.y + (_size.y - 30)/2 + 250}, 30,3, WHITE);
            
            counter++;

            if (counter > 25)
            {
                counter = 101;
                yesBtn->Draw();
                noBtn->Draw();
                if (yesBtn->isPressed(false))
                {
                    this->app->setNextScreen(new GuessWordScreen(this->app));
                }
                if (noBtn->isPressed(false))
                {
                    this->app->setNextScreen(new GameScreen(this->app));
                }
            }
        }
        if (modeGame == ModeGame::WRONG)
        {
            DrawRectangle(_origin.x, _origin.y + 250, _size.x + 150, _size.y, {255,98,137,255});
            DrawTextEx(this->app->asset->font50,"YOU CHOSE A WRONG ANSWER", {_origin.x + 225, _origin.y + (_size.y - 30)/2 + 250}, 30,3, WHITE);
            
            counter++;

            if (counter > 25)
            {
                counter = 101;
                yesBtn->Draw();
                noBtn->Draw();
                if (yesBtn->isPressed(false))
                {
                    this->app->setNextScreen(new GuessWordScreen(this->app));
                }
                if (noBtn->isPressed(false))
                {
                    this->app->setNextScreen(new GameScreen(this->app));
                }
            }
        }
    }
}

GuessWordScreen::GuessWordScreen(App* app)
: word(nullptr), viewScreen(nullptr), gameDef(nullptr), counter(0)
{
    this->app = app;
    this->mode = Mode::NOTSEARCH;
    this->modeGame = ModeGame::PREPARE;
    // backButton = new ReturnButton({1050, 112}, {45, 45}, RAYWHITE);

    constexpr Vector2 origin = {300, 50};
    constexpr Vector2 size = {700, 70};
    Color btnColor = {255,98,137,255};

    wordButton = new search_by_word_button(app->asset, {30, origin.y },  {125, 70}, btnColor, WHITE,21);
    defButton = new search_by_def_button(app->asset, {30 + wordButton->size.x, origin.y }, {125, 70}, btnColor, WHITE,21);

    addWordButton = new add_word_button(app->asset, {30, wordButton->origin.y + wordButton->size.y + 60}, {250, 100},btnColor,"Add a word","Add a word that you want",BLACK,24);

    historyButton = new history_button(app->asset, {30, addWordButton->origin.y + addWordButton->size.y + 10}, {250, 100},btnColor,"History","Words you have searched",BLACK,24);

    favoriteButton = new favorite_button(app->asset, {30, historyButton->origin.y + historyButton->size.y + 10}, {250, 100},btnColor,"Favorite","Your favorite word list",BLACK,24);

    gamesButton = new games_button(app->asset, {30, favoriteButton->origin.y + favoriteButton->size.y + 10}, {250, 100},btnColor,"Game","Enhance your vocabulary",BLACK,24);

    resetButton = new reset_button(app->asset, {30, gamesButton->origin.y + gamesButton->size.y + 10}, {250, 100}, btnColor,WHITE,24);

    yesBtn = new YesNo_button(app->asset, {origin.x + 50, origin.y + 350}, {300, 70}, btnColor, WHITE, "          Continue", 30);
    noBtn = new YesNo_button(app->asset, {origin.x + 500, origin.y + 350}, {300, 70}, btnColor, WHITE, "             Leave", 30);

    firstChoice = new Choices_button(app->asset, {origin.x, origin.y + 340}, {850, 75}, btnColor, WHITE, 30);
    secondChoice = new Choices_button(app->asset, {origin.x, firstChoice->origin.y + firstChoice->size.y + 10}, {850, 75}, btnColor, WHITE, 30);
    thirdChoice = new Choices_button(app->asset, {origin.x, secondChoice->origin.y + secondChoice->size.y + 10}, {850, 75}, btnColor, WHITE, 30);
    fourthChoice = new Choices_button(app->asset, {origin.x, thirdChoice->origin.y + thirdChoice->size.y + 10}, {850, 75}, btnColor, WHITE, 30);

    constexpr Vector2 mode_origin = {origin.x+size.x, origin.y};
    constexpr Vector2 mode_size = {150,size.y};
    modesButtons = new modes_buttons(app->asset, mode_origin, mode_size, WHITE,BLACK,25);
}

GuessWordScreen::~GuessWordScreen()
{
    delete defButton;
    delete wordButton;
    delete historyButton;
    delete favoriteButton;
    delete gamesButton;
    delete resetButton;
    delete viewScreen;
}