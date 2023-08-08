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

void Dictionary::removeWord(const string& str)
{
    Word* word;

    bool isExist = trie.findWhole(str, word);

    if (isExist)
    {
        trie.removeAKey(str);
        delete word;
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


    for(Definition* def : candidates)
    {
        def->value = editDistance(SplitDef(str), SplitDef(def->data));
        // cout << def->data << "\n";
    }

    std::sort(candidates.begin(), candidates.end(), [](Definition* def1, Definition* def2)
    {
        return def1->value < def2->value;
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

int editDistance(const vector<string>& vec1, const vector<string>& vec2) //DP to find the dissimilarity value of the two vectors
{
    int length1 = vec1.size();
    int length2 = vec2.size();

    if(length1 == 0 || length2 == 0)
        return (length1 > length2) ? length1 : length2;

    vector<vector<int>> dist;
    dist.resize(length1 + 1);
    for(int i = 0; i <= length1; ++i)
    {
        dist[i].resize(length2 + 1);
    }

    for (int i = 0; i <= length1; i++)
        dist[i][0] = i;
    for (int j = 0; j <= length2; j++)
        dist[0][j] = j;

    //cout << "loli\n";

    for (int i = 1; i <= length1; i++) {
        for (int j = 1; j <= length2; j++) {
            int cost;
            if(vec2[j - 1] == vec1[i - 1])
                cost = 0;
            else
                cost = 1;

            dist[i][j] = std::min(std::min(dist[i - 1][j] + 1, dist[i][j - 1] + 1), dist[i - 1][j - 1] + cost);
        }
    }
    //cout << dist[length1][length2];

    return dist[length1][length2];
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