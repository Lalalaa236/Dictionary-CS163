#include "WordList.h"

WordList::WordList(const vector<Word*>& list)
: origin({300, 235}), sizeEach({850, 150}), color(GRAY)
{
    // cout << "loli\n";
    int size = list.size();
    // cout << list[17]->data << "\n";
    // cout << "list size: " << size << "\n";
    int count = 0;
    for(int i = 0; i < size; ++i)
    {
        if(!list[i])
            continue;
        else
        {
            WordButton* newWord = new WordButton(list[i], {this->origin.x, this->origin.y + 20 + this->sizeEach.y * count}, this->sizeEach, this->color);
            word.push_back(newWord);
            ++count;
        }
    }
}

Word* WordList::getWord()
{
    int size = word.size();
    // cout << size << "\n";
    BeginScissorMode(300, 235, 850, 525);
    for(int i = 0; i < size; ++i)
    {
        if(word[i] && word[i]->isPressed(true) && inRange())
        {
            EndScissorMode();
            return word[i]->data; //cout << word[i]->data->data << "\n";
        }
    }
    EndScissorMode();
    return nullptr;
}

void WordList::Draw()
{
    BeginScissorMode(300, 235, 850, 525);
    int size = word.size();
    for(int i = 0; i < size; ++i)
    {
        word[i]->button.y = this->origin.y + (this->sizeEach.y + 20) * i;
        word[i]->Draw({this->origin.x, this->origin.y + (this->sizeEach.y + 20) * i});
    }
    float offset = GetMouseWheelMove() * 30;
    // cout << offset << "\n";
    if(size > 3)
    {
        if((this->origin.y + offset  <= 760 - (this->sizeEach.y + 20) * (size - 1) - sizeEach.y + 20) && (offset < 0))
            this->origin.y = 760 - (this->sizeEach.y + 20) * (size - 1) - sizeEach.y;
        else if(this->origin.y + offset >= 180 && offset > 0)
            this->origin.y = 235;
        else
            this->origin.y += offset;
    }
    EndScissorMode();
}

bool WordList::inRange()
{
    Vector2 mouse = GetMousePosition();
    if(mouse.y >= 235 && mouse.y < 725)
        return true;
    return false;
}