#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::cin;
using std::cout;
using std::vector;

string Normalize(const string& s);

template<class Data> 
class trieNode
{
    public:
        Data data;// data
        trieNode<Data>* children[256];// branches, ascii value from 32 to 126 
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
        bool findWhole(const string& str, Data& data);// find a word in the trie
        vector<Data> findPrefix(const string& s);// get all the words with this prefix
        void getRes(trieNode<Data>* cur, vector<Data>& res);

        bool isEmpty(trieNode<Data>* cur);// check if cur is not prefix of any other word
        void removeAKey(const string& str);

    private:
        trieNode<Data>* root;
        void deallocate(trieNode<Data>*& root);
        trieNode<Data>* remove(trieNode<Data>*& root, const string& str, int depth = 0);
};

template<class Data>
trieNode<Data>::trieNode()
: data(), endOfWord(false)
{
    for(int i = 0; i < 256; ++i)
    {
        children[i] = nullptr;
    }
}

template<class Data>
trieNode<Data>::trieNode(Data data)
: data(data), endOfWord(false)
{
    for(int i = 0; i < 256; ++i)
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
    //cout << "Deleted trie\n";
}

template<class Data>
void Trie<Data>::deallocate(trieNode<Data>*& root)
{
    if(!root)
        return;
    
    for(int i = 0; i < 256; ++i)
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
    string cpy = Normalize(str);
    for(int i = 0; i < length; ++i)
    {
        if(cpy[i] < -128 || cpy[i] > 127)
        {
            cout << "Invalid character!\n";
            return false;
        }    
        int index = cpy[i] + 128;
        
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
bool Trie<Data>::findWhole(const string& str, Data& data)
{
    if(!this->root)
        return false;
    std::string copy_str = str;
    copy_str = Normalize(copy_str);
    trieNode<Data>* cur = this->root;
    int length = copy_str.length();

    for(int i = 0; i < length; ++i)
    {
        int index = copy_str[i] + 128;

        if(!cur->children[index])
            return false;
        
        cur = cur->children[index];
    }

    if(cur->endOfWord)
    {
        data = cur->data;
        return true;
    }
    
    return false;
}

template<class Data>
vector<Data> Trie<Data>::findPrefix(const string& s)
{
    string copy_s = s;
    copy_s = Normalize(copy_s);
    int length = copy_s.length();
    if(length == 0)
        return vector<Data>();
    trieNode<Data>* cur = this->root;
    for(int i = 0; i < length; ++i)
    {
        int val = (int)copy_s[i] + 128;
        if(val > 256 || val < 0)
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
    for(int i = 0; i < 256; ++i)
        Trie<Data>::getRes(cur->children[i], res);
}

template<class Data>
bool Trie<Data>::isEmpty(trieNode<Data>* cur)
{
    for (int i = 0; i < 256; i++)
    {
        if (cur->children[i])
            return false;

    }
        return true;
}

template<class Data>
void Trie<Data>::removeAKey(const string& str)
{
    int depth = 0;
    remove(this->root, str, depth);
    cout << "A word is removed.";
}

template<class Data>
trieNode<Data>* Trie<Data>::remove(trieNode<Data>*& root, const string& str, int depth)
{
    if (!root)
        return root;

    if (depth == str.length())
    {
        if (root->endOfWord)
            root->endOfWord = false;

        return root;
    }

    int index = str[depth] + 128;

    root->children[index] = remove(root->children[index], str, depth + 1);

    return root;
}

#endif 
