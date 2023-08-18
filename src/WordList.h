#ifndef WORDLIST_H
#define WORDLIST_H

#include <vector>
#include "raylib.h"
#include "Dictionary.h"
#include "Button.h"

using std::vector;

class WordList
{
private:
    vector<WordButton*> word;
    Vector2 origin;
    Vector2 sizeEach;
    Color color;
public:
    WordList() = default;
    WordList(const vector<Word*>& list);
    WordButton* getWord();
    void Draw();
    bool inRange();
};

#endif