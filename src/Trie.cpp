#include "Trie.h"

string Normalize(const string& s)
{
    string cpy = s;
    for(int i = 0; i < cpy.length(); ++i)
    {
        if(isalpha(cpy[i]))
        {
            cpy[i] = tolower(cpy[i]);
        }
    }
    return cpy;
};