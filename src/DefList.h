#ifndef DEFLIST_H
#define DEFLIST_H

#include <vector>
#include "raylib.h"
#include "Dictionary.h"
#include "Button.h"

using std::vector;

class DefList
{
private:
    Word* word;
    vector<EditDefButton*> defs;
    Vector2 origin;
    Color color;
    Asset* asset;
    float allSize;
public:
    DefList(Asset* asset, const vector<Definition*>& list, Word* word, Vector2 origin);
    ~DefList(); 
    EditDefButton* getDef();
    void Draw();
    bool inRange();
};

#endif