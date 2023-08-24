#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Trie.h"
#include <fstream>
#include <algorithm>


using std::ifstream;
using std::ofstream;
using std::pair;

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

class DefWord
{
public:
    string data;
    vector<Definition*> defs;

    DefWord(const string& data);
};

class Definition
{
public:
    int value;
    string data;
    Word* word;

    Definition(const string& data);
    ~Definition();
};

class Dictionary
{
public:
    vector<Word*> history;

    Trie<Word*> trie; // trie containing all words
    Trie<DefWord*> defWords; // trie containing all word in definition

    vector<Word*> words; //save all the words in dict for playing game
    vector<Definition*> allDef;//save all the def in dict for playing game

    typedef pair<vector<pair<Word*, bool>>, Definition*> gameRes;

    Dictionary();
    void insertWord(const string& str); //function for user to insert word
    void insertDef(const string& str, Word*& word); //function for user to insert a definition to an already existing word
    //functions type should be changed in order to implement the front end (void -> ???)
    void editDef(const string& word_edit_def,const string& old_def,const string& new_def);

    gameRes chooseWord();


    vector<Word*> searchWord(const string& str);
    vector<Word*> searchDef(const string& str);

    void loadData(const string& filePath);

    void deleteDict();
    void addDefWord(Definition*& def, const string& s);
    void removeWord(const string& str, const string filePath); //function for user to delete a word

    void addToFavList(Word* word, const string& fileDir);
    void removeFromFavList(Word* word, const string& fileDir);
    vector<Word*> viewFavList(const string& fileDir);

    void addToHis(Word* word, const string& fileDir);
    vector<Word*> getHis(const string& fileDir);

    vector<Word*> randomWord();
    
    void resetDictionary();

    void guessDef(Word*& word, string& def_ans, int& pos_ans, vector<string>& multi_choices);
};

vector<string> Split(const string& s); // function to split a string into word and def
vector<string> SplitDef(const string& s); // function to split the definition
 //function to add def word

string NormalizeDef(const string& s);
string mergeDef(const vector<string>& vec);
void initConcat(string str, vector<int>& Z); // helper func for numPattern
int numPattern(const string& text, const string& pattern); // Z func

#endif