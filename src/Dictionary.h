#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Trie.h"

class Definition;

class Word
{
public:
    string data; //the word
    int index; // index 
    vector<Definition*> def; // definitions vector
    bool favourite; // favourite word or not

    Word();
    Word(const string &data);
    ~Word();
};

class Definition
{
public:
    string data;
    Word* word;

    Definition(const string& data);
    ~Definition();
};

class Dictionary
{
public:
    vector<Word*> history;
    Trie<Word> trie;

    Dictionary();
    void insertWord(const string& str);
};

#endif