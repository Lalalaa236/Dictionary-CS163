#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Trie.h"
#include <fstream>
#include <string>
using std::ifstream;
using std::ofstream;

class Definition;

class Word
{
public:
    string data; //the word
    int index; // index 
    vector<Definition*> defs; // definitions vector
    bool favourite; // favourite word or not

    Word();
    Word(const string& data);
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
    Trie<Word*> trie;
    vector<Word*> words; //save all the words in dict for playing game
    vector<string> def_game;//save all the def in dict for playing game

    Dictionary();
    void insertWord(const string& str); //function for user to insert word
    void insertDef(const string& str, Word*& word); //function for user to insert a definition to an already existing word
    //functions type should be changed in order to implement the front end (void -> ???)
    void editDef(const string& word_edit_def,const string& old_def,const string& new_def);
    vector<Word*> searchWord(const string& str);

    void loadData(const string& filePath);
};

vector<string> Split(const string& s); // function to split a string into word and def

#endif