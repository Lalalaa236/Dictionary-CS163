#include "WordList.h"

WordList::WordList(const vector<Word*>& list)
: origin({300, 200}), sizeEach({850, 150}), color(GRAY)
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
            cout << i << ": " << i << "\n";
            WordButton* newWord = new WordButton(list[i], {this->origin.x, this->origin.y + 20 + this->sizeEach.y * count}, this->sizeEach, this->color);
            word.push_back(newWord);
            ++count;
        }
    }
}

Word* WordList::getWord(int i)
{
    return word[i]->data;
}

void WordList::Draw()
{
    BeginScissorMode(300, 200, 850, 525);
    int size = word.size();
    for(int i = 0; i < size; ++i)
    {
        word[i]->Draw({this->origin.x, this->origin.y + (this->sizeEach.y + 20) * i});
    }
    float offset = GetMouseWheelMove() * 30;
    // cout << offset << "\n";
    if((this->origin.y  <= 725 - (this->sizeEach.y + 20) * (size - 1) - sizeEach.y + 20) && (offset < 0))
        this->origin.y = this->origin.y;
    else if(this->origin.y >= 180 && offset > 0)
        this->origin.y = this->origin.y;
    else
        this->origin.y += offset;
    EndScissorMode();
}