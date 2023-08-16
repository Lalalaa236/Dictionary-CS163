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
    vector<Word*> list;
public:
    WordList() = default;
    WordList(const vector<Word*>& getList);
    Word* getWord(int i);
    void DrawWordList(const vector<Word*>& getList);

};

#endif