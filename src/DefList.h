#ifndef DEFLIST_H
#define DEFLIST_H

#include <vector>
#include "raylib.h"
#include "Dictionary.h"
#include "Button.h"

using std::vector;

class DefList
{
public:
    Word* word;
    vector<EditDefButton*> defs;
    Vector2 origin;
    Color color;
    Asset* asset;
    float allSize;
    DefList(Asset* asset, const vector<Definition*>& list, Word* word, Vector2 origin);
    ~DefList(); 
    EditDefButton* getDef();
    void Draw();
    bool inRange();
};

#endif