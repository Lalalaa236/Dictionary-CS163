#include "Trie.h"

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
Trie<Data>::Trie()
: root(nullptr)
{}

template<class Data>
Trie<Data>::~Trie()
{
    deallocate(this->root);
}

template<class Data>
void Trie<Data>::deallocate(trieNode<Data>* &root)
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
        this->root = new trieNode();
    
    trieNode* cur = this->root;

    int length = str.length();
    for(int i = 0; i < length; ++i)
    {
        int index = str[i] - '!';
        
        if(!cur->children[index])
            cur->children[index] = new trieNode();

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