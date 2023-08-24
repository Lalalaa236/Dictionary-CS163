#include "DefList.h"

DefList::DefList(Asset* asset, const vector<Definition*>& list, Word* word, Vector2 origin)
: asset(asset), word(word), allSize(0), origin(origin)
{
    for(auto def : list)
    {
        if(!def)
            continue;
        EditDefButton* cur = new EditDefButton(asset, def, origin, PINK);
        defs.push_back(cur);
        allSize += cur->displayDef.height + 20;
    }


}

EditDefButton* DefList::getDef()
{
    int size = defs.size();
    // cout << size << "\n";
    BeginScissorMode(30, 50, 1120, 665);
    for(int i = 0; i < size; ++i)
    {
        if(defs[i] && defs[i]->isPressed(false) && inRange())
        {
            EndScissorMode();
            return defs[i]; //cout << word[i]->data->data << "\n";
        }
    }
    EndScissorMode();
    return nullptr;
}

void DefList::Draw()
{
    BeginScissorMode(30, 50, 1120, 665);
    int size = defs.size();
    float curSize = 0;
    for(int i = 0; i < size; ++i)
    {
        defs[i]->button.y = this->origin.y + curSize;
        defs[i]->Draw({this->origin.x, this->origin.y + curSize});
        curSize += defs[i]->displayDef.height + 20;
    }
    float offset = GetMouseWheelMove() * 30;
    if(size > 3)
    {
        if(this->origin.y + offset  <= 715 - allSize + 20 && (offset < 0))
            this->origin.y = 715 - allSize + 20;
        else if(this->origin.y + offset >= 180 && offset > 0)
            this->origin.y = 180;
        else
            this->origin.y += offset;
    }
    EndScissorMode();
}

bool DefList::inRange()
{
    Vector2 mouse = GetMousePosition();
    if(mouse.y >= 180 && mouse.y < 725)
        return true;
    return false;
}

DefList::~DefList()
{
    int size = defs.size();
    for(int i = 0; i < size; ++i)
    {
        delete defs[i];
    }
}