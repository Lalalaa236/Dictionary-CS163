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
    Word* word;
    if(trie.findWhole(str, word))
    {
        cout << "Duplicated word!\n";
        delete word;
        return;
    }

    Word* newWord = new Word(str);
    trie.insert(str, newWord);
    words.push_back(newWord);  // for game
}

void Dictionary::insertDef(const string& str, Word*& word)
{
    Definition* def = new Definition(str);
    def->word = word;
    word->defs.push_back(def);
}

void Dictionary::loadData(const string& filePath)
{
    ifstream fin(filePath);
    if(!fin.is_open())
    {
        cout << "Error opening file!\n";
        return;
    }

    string line;
    int linecnt = 0;
    while(getline(fin, line))
    {
        ++linecnt;
        //cout << "line " << linecnt << " :" << line << "\n";

        vector<string> current = Split(line);
        // cout << "current: " << current[0] << "\n";
        // cout << current[1] << "\n\n";
        
        if(current.size() != 2)
        {
            cout << "Skipping line: " << linecnt << "\n"; 
            //continue;
        }

        else
        {
            if(!current[0].empty())
            {
                current[0][0] = toupper(current[0][0]);
                std::transform(current[0].begin() + 1, current[0].end(), current[0].begin() + 1, ::tolower);
                Word* newWord = new Word(current[0]);
                words.push_back(newWord); 
            }
            Word* word;
            if(!trie.findWhole(current[0], word))
            {
                word = new Word(current[0]);
                if(!trie.insert(current[0], word))
                {
                    cout << "Cannot insert: " << current[0] << "\n";
                    continue;
                }
            }
            //cout << "Inserted successfully!\n";
            Definition* def = new Definition(current[1]);
            def->word = word;
            word->defs.push_back(def);
            def_game.push_back(def);
        }
    }

    fin.close();
}

vector<Word*> Dictionary::searchWord(const string& str)
{
    return trie.findPrefix(str);
}

vector<string> Split(const string& s)
{
    vector<string> res;
    string tmp;
    if(s.length() == 0)
    {
        cout << "Nothing to split!\n";
        return res;
    }

    int i = 0;
    for(auto c : s)
    {
        if(c == (char)40)
            break;
        else
            tmp.push_back(c);
        ++i;
    }
    tmp = tmp.substr(0, tmp.length() - 1);
    res.push_back(tmp);

    tmp.clear();
    tmp = s.substr(i, s.length() - 1);
    res.push_back(tmp);

    return res;
}

void Dictionary::editDef(const string& word_edit_def, const string& old_def,const string& new_def)
{
    Word* word;
    if(trie.findWhole(word_edit_def, word))
    {
        int defIndex = -1;
        for(int i = 0; i < word->defs.size(); ++i)
        {
            if(word->defs[i]->data.find(old_def) != string::npos)
            {
                defIndex = i;
                break;
            }
        }
        if(defIndex == -1)
        {
            cout << "Definition not found!\n";
            return;
        }
        Definition* def = word->defs[defIndex];
        def->data.replace(def->data.find(')') + 2, def->data.size() - (def->data.find(')') + 2), new_def);   
    }

    else
    {
        cout << "Word not found\n";
    }
}

void playGame(Dictionary& dictionary) 
{
    if(dictionary.words.size() == 0) {
        return;
    }
    // random word
    int wordIndex = rand() % dictionary.words.size();
    Word* word_random = dictionary.words[wordIndex];
    Word* word;
    if (dictionary.trie.findWhole(word_random->data,word))
    {
        cout << "Guess the definition of: " << word->data << "\n";
        string def_ans = word->defs[rand() % word->defs.size()]->data;
        int pos_ans =  rand() % 4; //position of the answer
        for (int i=0;i<4;i++)
        {
            if (i==pos_ans)
                cout <<def_ans<<std::endl;
            else
            {
                string def_rand = dictionary.def_game[rand() % dictionary.def_game.size()]->data;
                cout << def_rand << std::endl;
            }
          
        }
        string guess;
        cin >> guess;
        if(guess == def_ans) {
            cout << "Correct!\n";
        } 
        else {
            cout << "Incorrect, the word was: " << def_ans<< "\n";
        }
    }
  
}
void Dictionary::deleteDict()
{
    trie.~Trie();

    history.clear();

    return;
}

void Dictionary::removeWord(const string& str, const string filePath)
{
    Word* word;

    bool isExist = trie.findWhole(str, word);

    if (isExist)
    {
        trie.removeAKey(str);
        std::ifstream fin(filePath);
        std::string tempFilePath = filePath.substr(0, filePath.size() - 4) + "_removeWord.txt";
        std::ofstream fout(tempFilePath);

        std::string deleteLine = word->data + " ("; // Ex: "foo ("
        std::string line;

        while (getline(fin, line))
        {
            long long unsigned int position = line.find(deleteLine);

            if (position == string::npos)
            {
                fout << line << std::endl;
            }
            
        }

        fin.close();
        fout.close();
        remove(filePath.c_str());
        rename(tempFilePath.c_str(), filePath.c_str());

        // delete word;
        return;
    }

    std::cout << "The word does not exist.";
    return;
}

void Dictionary::addToFavList(Word* word)
{
    std::ofstream fout;
    fout.open("../data/FavoriteList.txt", std::ios_base::app);

    for (int i = 0; i < word->defs.size(); i++)
    {
        fout << word->data << " " << word->defs[i]->data;
        fout << std::endl;
    }

    fout.close();
}

void Dictionary::removeFromFavList(Word* word)
{
    std::ifstream fin("../data/FavoriteList.txt");
    std::ofstream fout("../data/FavoriteList_removeWord.txt");

    std::string deleteLine = word->data + " ("; // Ex: "foo ("
    std::string line;

    bool deleted = false;

    while (getline(fin, line))
    {
        long long unsigned int position = line.find(deleteLine);

        if (position == string::npos)
        {
            fout << line << std::endl;
        }
        else
        {
            deleted = true;
        }
    }

    if (deleted)
        std::cout << "A word is removed from favorite list!";

    fin.close();
    fout.close();
    remove("../data/FavoriteList.txt");
    rename("../data/FavoriteList_removeWord.txt", "../data/FavoriteList.txt");
}
int main() {
    Dictionary myDict;
    myDict.loadData("C:\\Users\\Hisokaxxzk\\Dictionary-CS163\\data\\Eng-Eng.txt");
    // myDict.editDef("A b c","The first three letters of the alphabet, used for the whole alphabet.","Thinh dep trai");
    // cout <<"Edited succesfully  \n";
    // std::string test;
    // getline(cin,test) ;
    // vector<Word*> results = myDict.searchWord(test);
    // cout << "Search results for prefix \"" << test << "\":\n";
    // for (Word* word : results) {
    //     if (word != nullptr) {
    //         cout << word->data << "\n";

    //         // Optionally print definitions
    //         for (Definition* def : word->defs) {
    //             if (def != nullptr) {
    //                 cout << "  - " << def->data << "\n";
    //             }
    //         }
    //     }
    // }
    playGame (myDict);
    return 0;
}
