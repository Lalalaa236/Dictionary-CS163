#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>

using std::string;

template<class Data> 
class trieNode
{
    public:
        Data data;// data
        trieNode<Data>* children[94];// branches, ascii value from 33 to 127 
        bool endOfWord;

        trieNode(Data data);// constructor
        ~trieNode();// destructor
};

template<class Data>
class Trie
{
    public:
        Trie();// constructor
        ~Trie();// destructor

        trieNode<Data>* getRoot();// func to get root
        void insert(const string &str);

    private:
        trieNode* root;
};

#endif 