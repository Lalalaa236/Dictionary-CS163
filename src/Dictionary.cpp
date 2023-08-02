#include "Dictionary.h"

Word::Word()
: data(), favourite(false)
{}

Word::Word(const string& data)
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

void Dictionary::insertWord(const string& str) //insert new word into the dictionary
{
    if(trie.findWhole(str))
    {
        cout << "Duplicated word!\n";
        return;
    }

    Word word(str);
    trie.insert(str, word);
}

vector<string> Split(const string& s)
{
    vector<string> res;
    string tmp;
    int i = 0;
    for(auto c : s)
    {
        if(c == (char)40)
        {
            ++i;
            break;
        }
        else
            tmp.push_back(c);
    }
    tmp = tmp.substr(0, tmp.length() - 1);
    res.push_back(tmp);

    tmp.clear();
    tmp = s.substr(i + 1, s.length() - 1);
    res.push_back(tmp);

    return res;
}