#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Trie.h"

class Definition;

class Word
{
public:
    string data;
    string type;
    vector<Definition*> def;
    bool favourite;

    Word() = default;
    Word(const string &data);
    ~Word();
};

#endif