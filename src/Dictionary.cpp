#include "Dictionary.h"

Word::Word()
: data(), favourite(false)
{}

Word::Word(const string& data)
: data(data), favourite(false)
{}

Word::~Word() 
{}

DefWord::DefWord(const string& data)
: data(data)
{}

Definition::Definition(const string& data)
: data(data), word(nullptr), value(0)
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
            Word* word;
            if(!trie.findWhole(current[0], word))
            {
                word = new Word(current[0]);
                if(!trie.insert(current[0], word))
                {
                    cout << "Cannot insert: " << current[0] << "\n";
                    delete word;
                    word = nullptr;
                    continue;
                }
            }
            //cout << "Inserted successfully!\n";
            Definition* def = new Definition(current[1]);
            def->word = word;
            word->defs.push_back(def);
            words.push_back(word);
            allDef.push_back(def);
            addDefWord(def, current[1]);
        }
    }

    fin.close();
}

vector<Word*> Dictionary::searchWord(const string& str)
{
    if(str.length() == 0)
        return vector<Word*>();
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

vector<string> SplitDef(const string& s)
{
    vector<string> res;
    string tmp;

    for(auto c : s)
    {
        if(c == ' ')
        {
            tmp = NormalizeDef(tmp);
            if(!tmp.empty())
                res.push_back(tmp);
            tmp.clear();
            continue;
        }
        else
            tmp.push_back(c);
    }
    tmp = NormalizeDef(tmp);
    if(!tmp.empty())
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
                string def_rand = dictionary.allDef[rand() % dictionary.allDef.size()]->data;
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

void Dictionary::addDefWord(Definition*& def, const string& s)
{
    vector<string> words = SplitDef(s);
    
    for(auto tmp : words)
    {
        DefWord* newWord;
        if(!defWords.findWhole(tmp, newWord))
        {
            newWord = new DefWord(tmp);
            if(!defWords.insert(tmp, newWord))
            {
                cout << "Cannot insert: " << newWord->data;
                delete newWord;
                newWord = nullptr;
                continue;
            }
        }
        newWord->defs.push_back(def);
        // static int i = 0;
        // while(i++ < 1)
        // {
        //     cout << newWord->data << "\n";
        //     cout << newWord->defs[0]->data << "\n";
        // }
        // if(defWords.findWhole("()", newWord))
        //     cout << "YES";
        // cout << "tmp: " << tmp << "\n";
    }
}

vector<Word*> Dictionary::searchDef(const string& str)
{
    if(str.length() == 0)
        return vector<Word*>();
    
    for(Definition* def : allDef)
        def->value = 0;

    vector<Word*> res;
    vector<Definition*> candidates;

    for(string tmp : SplitDef(str))
    {
        DefWord* cur;
        if(!defWords.findWhole(tmp, cur))
        {
            continue;
        }
        else
        {
            for(Definition* def : cur->defs)
            {
                def->value += 1;
                if(def->value == 1)
                    candidates.push_back(def);
            }
        }
    }

    // for(Definition* def : candidates)
    // {
    //     cout << def->word->data << "\n\n";
    // }

    // for(Definition* def : allDef)
    // {
    //     if(def->value >= 1.00)
    //         candidates.push_back(def);
    // }
    // cout << candidates.size() << "\n";


    for(auto def : candidates)
    {
        def->value = numPattern(mergeDef(SplitDef((def->data))), mergeDef(SplitDef(str)));
        // cout << def->data << "\n";
    }

    std::sort(candidates.begin(), candidates.end(), [](auto def1, auto def2)
    {
        return def1->value > def2->value;
    });
    

    int size = candidates.size();

    for(int i = 0; i < 50 && i < size; ++i)
    {
        res.push_back(candidates[i]->word);
    }

    for(int i = 0; i < 50 && i < size; ++i)
    {
        bool isRepeated = false;
        for(int j = 0; j < i; ++j)
        {
            if(res[i] == res[j])
            {
                isRepeated = true;
                break;
            }
        }

            if(isRepeated)
                res[i] = nullptr;
    }

    return res;
}

string NormalizeDef(const string& s)
{
    string specialChar = ",.?-:;\"'{}[]|!@#$%^&*()~`/\\";

    int length = s.length();
    string cpy = s;
    for(int i = 0; i < cpy.length(); ++i)
    {
        if(isalpha(cpy[i]))
        {
            cpy[i] = tolower(cpy[i]);
        }
    }
    while(specialChar.find(cpy.front()) != string::npos)
    {
        cpy = cpy.substr(1, cpy.length() - 1);
    }
    while(specialChar.find(cpy.back()) != string::npos)
    {
        cpy = cpy.substr(0, cpy.length() - 1);;
    }
    return cpy;
}

string mergeDef(const vector<string>& vec)
{
    string res;
    int length = vec.size();
    for(int i = 0; i < length; ++i)
    {
        if(i == length - 1)
        {
            res += vec[i];
            break;
        }
        res += vec[i];
        res += " ";
        
    }

    return res;
}

void initConcat(string str, vector<int>& Z)
{
    int n = str.length();
    int left, right, k;
 
    left = right = 0;
    for (int i = 1; i < n; ++i)
    {
        if (i > right)
        {
            left = right = i;
 
            while (right < n && str[right - left] == str[right])
                right++;
            Z[i] = right - left;
            right--;
        }
        else
        {
            
            k = i - left;
            
            if (Z[k] < right - i + 1)
                Z[i] = Z[k];
            else
            {
                left = i;
                
                while (right < n && str[right - left] == str[right])
                    right++;
                Z[i] = right - left;
                right--;
            }
        }
    }
}

int numPattern(const string& text, const string& pattern) // Z func
{
    int res = 0;
    string concat = pattern + "$" + text;
    int l = concat.length();
 
    vector<int> Z(l);
    initConcat(concat, Z);
 
    for (int i = 0; i < l; ++i)
    {
        if (Z[i] == pattern.length())
            ++res;
    }
    
    return res;
}

void Dictionary::addToFavList(Word* word)
{
    word->favourite = true;
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
    word->favourite = false;
    
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

vector<Word*> Dictionary::viewFavList()
{
    std::ifstream fin("../data/FavoriteList.txt");

    vector<Word*> favList;

    std::string line;
    std::string curWord;

    while(getline(fin, line))
    {

        vector<string> current = Split(line);

        if (current.size() == 2)
        {
            Word* word;
            if(current[0] != curWord)
            {

                curWord = current[0];
                word = new Word(current[0]);

                favList.push_back(word);
            }
            Definition* def = new Definition(current[1]);
            word->defs.push_back(def);
        }
    }

    for (int i = 0; i < favList.size(); i++)
    {
        std::cout << i + 1 << ". " << favList[i]->data << '\n';
        for (int j = 0; j < favList[i]->defs.size(); j++)
        {
            std::cout << "  " << favList[i]->defs[j]->data << '\n';
        }
    }

    return favList;
}