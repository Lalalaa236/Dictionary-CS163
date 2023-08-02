#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::vector;

template<class Data> 
class trieNode
{
    public:
        Data data;// data
        trieNode<Data>* children[94];// branches, ascii value from 33 to 127 
        bool endOfWord;

        trieNode();
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
        
        bool insert(const string& str, const Data& data);// insert data into trie
        bool findWhole(const string& str);// find a word in the trie
        vector<Data> findPrefix(const string& s);// get all the words with this prefix
        void getRes(trieNode<Data>* cur, vector<Data>& res);

    private:
        trieNode<Data>* root;
        void deallocate(trieNode<Data>*& root);
};

template<class Data>
trieNode<Data>::trieNode()
: data(), endOfWord(false)
{
    for(int i = 0; i < 94; ++i)
    {
        children[i] = nullptr;
    }
}

template<class Data>
trieNode<Data>::trieNode(Data data)
: data(data), endOfWord(false)
{
    for(int i = 0; i < 94; ++i)
    {
        children[i] = nullptr;
    }
}

template<class Data>
trieNode<Data>::~trieNode()
{}

template<class Data>
Trie<Data>::Trie()
: root(nullptr)
{}

template<class Data>
Trie<Data>::~Trie()
{
    deallocate(this->root);
    cout << "Deleted trie\n";
}

template<class Data>
void Trie<Data>::deallocate(trieNode<Data>*& root)
{
    if(!root)
        return;
    
    for(int i = 0; i < 94; ++i)
    {
        deallocate(root->children[i]);
    }

    delete root;
    root = nullptr; 
}

template<class Data>
bool Trie<Data>::insert(const string& str, const Data& data)
{
    if(!this->root)
        this->root = new trieNode<Data>();
    
    trieNode<Data>* cur = this->root;

    int length = str.length();
    for(int i = 0; i < length; ++i)
    {
        int index = str[i] - '!';
        
        if(!cur->children[index])
            cur->children[index] = new trieNode<Data>();

        cur = cur->children[index]; 
    }

    if(!cur->endOfWord)
    {
        cur->endOfWord = true;
        cur->data = data;
        return true;
    }
    
    return false;
}

template<class Data>
bool Trie<Data>::findWhole(const string& str)
{
    if(!this->root)
        return false;
    
    trieNode<Data>* cur = this->root;
    int length = str.length();

    for(int i = 0; i < length; ++i)
    {
        int index = str[i] - '!';

        if(!cur->children[index])
            return false;
        
        cur = cur->children[index];
    }

    if(cur->endOfWord)
        return true;
    return false;
}

template<class Data>
vector<Data> Trie<Data>::findPrefix(const string& s)
{
    int length = s.length();
    if(length == 0)
        return vector<Data>();
    trieNode<Data>* cur = this->root;
    for(int i = 0; i < length; ++i)
    {
        int val = (int)s[i] - 33;
        if(val > 93 || val < 0)
            return vector<Data>();
        if(cur->children[val] == nullptr)
            return vector<Data>();

        cur = cur->children[val];
    }
    vector<Data> res;
    Trie<Data>::getRes(cur, res);
    return res;
}

template<class Data>
void Trie<Data>::getRes(trieNode<Data>* cur, vector<Data>& res)
{
    if(cur == nullptr)
        return;

    if(cur->endOfWord)
        res.push_back(cur->data);
    for(int i = 0; i < 94; ++i)
        Trie<Data>::getRes(cur->children[i], res);
}

#endif 