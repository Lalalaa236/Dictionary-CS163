#include "Dictionary.h"

Word::Word()
: data(), favourite(false)
{}

Word::Word(const string &data)
: data(data), favourite(false)
{}

Word::~Word() 
{}

Definition::Definition(const string& data)
: data(data), word(nullptr) 
{}

Definition::~Definition()
{}

Dictionary::Dictionary()
{}

void Dictionary::insertWord(const string& str)
{
    if(trie.findWhole(str))
    {
        cout << "Duplicated word!\n";
        return;
    }

    Word word(str);
    trie.insert(word);

}