#include "Dictionary.h"

Word::Word()
: data(), favourite(false)
{}

Word::Word(const string& data)
: data(data), favourite(false)
{}

// Word::~Word() 
// {}

DefWord::DefWord(const string& data)
: data(data)
{}

Definition::Definition(const string& data)
: data(data), word(nullptr), value(0)
{}

// Definition::~Definition()
// {}

Dictionary::Dictionary()
{}

void Dictionary::insertWord(const string& str) 
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
    ifstream fin(filePath + "data.txt");
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
            bool insert = false;
            Word* word;
            if(!trie.findWhole(current[0], word))
            {
                word = new Word(current[0]);
                insert = true;
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
            int index = words.size();
            if(insert)
                words.push_back(word);
            word->index = index;
            allDef.push_back(def);
            addDefWord(def, current[1]);
        }
    }

    fin.close();
    fin.open(filePath + "FavoriteList.txt");
    string prev;
    while(getline(fin, line))
    {
        if(prev != line)
        {
            Word* word;
            if(trie.findWhole(Normalize(line), word))
                word->favourite = true;
            prev = line;
        }
    }
    fin.close();
}

vector<Word*> Dictionary::searchWord(const string& str)
{
    if(str.length() == 0)
        return vector<Word*>();
    vector<Word*> res = trie.findPrefix(str);
    if(res.size() > 100)
        res.resize(100);
    return res;
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

void Dictionary::editDef(const string& fileDir, const string& newstring, const string& oldstring)
{
    // Word* word;
    // if(trie.findWhole(word_edit_def, word)) {
    //     int defIndex = -1;
    //     for(int i = 0; i < word->defs.size(); ++i) {
    //         if(word->defs[i]->data.find(old_def) != string::npos) {
    //             defIndex = i;
    //             break;
    //         }
    //     }
    //     if(defIndex == -1) return;
    //     Definition* def = word->defs[defIndex];
    //     def->data.replace(def->data.find(')') + 2, def->data.size() - (def->data.find(')') + 2), new_def);   
    // } else return;
    int count = 0;
    const string oldfilename = fileDir + "data.txt";
    const string newfilename = fileDir + "newData.txt";
    ifstream fin(oldfilename);
    ofstream fout;
    fout.open(newfilename);
    string tmp;
    while(getline(fin, tmp))
    {
        if(count != 0)
        {
            if(tmp != oldstring)
                fout << "\n" << tmp;
            else
                fout << "\n" << newstring;
        }
        else
        {
            if(tmp != oldstring)
                fout << tmp;
            else
                fout << newstring;
        }
        ++count;
        
    }
    fin.close();
    fout.close();
    remove(oldfilename.c_str());
    rename(newfilename.c_str(), oldfilename.c_str());

}

void Dictionary::guessDef(Word*& gameWord, string& defAns, int& posAns, vector<string>& multiChoices) 
{
    if(words.size() == 0) {
        return;
    }
    // random word
    int wordIndex = rand() % words.size();
    Word* word_random = words[wordIndex];
    Word* word;
    vector<string> multi_choices;
    if (trie.findWhole(word_random->data,word))
    {
        gameWord = word;
        cout << "Guess the definition of: " << word->data << "\n";
        string def_ans = word->defs[rand() % word->defs.size()]->data;
        int pos_ans =  rand() % 4; //position of the answer
        for (int i=0;i<4;i++)
        {
            if (i==pos_ans)
            {
                multiChoices.push_back(def_ans);
                cout <<def_ans << def_ans.length() <<std::endl;
            }
            else
            {
                string def_rand = allDef[rand() % allDef.size()]->data;
                multiChoices.push_back(def_rand);
                cout << def_rand << def_rand.length() << std::endl;
            }
          
        }
        defAns = def_ans;
        posAns = pos_ans;
    }
}

Dictionary::gameRes Dictionary::chooseWord(Definition*& gameDef, string& wordAns, int& posAns, vector<string>& multiChoices) 
{
	Definition* ques = allDef[rand() % allDef.size()];
    gameDef = ques;

	Word* ans = ques->word;
    wordAns = ans->data;

	vector<pair<Word*, bool>> res(4);
	int ans_index = rand() % 4;
    posAns = ans_index;

	res[ans_index] = {ans, true};

	for(int i = 0; i < 4;)
	{
		if(i != ans_index)
		{
			bool exist = false;
			res[i] = {words[rand() % words.size()], false};
			for(int j = 0; j < i; ++j)
			{
				if(res[j].first == res[i].first)
				{
					exist = true;
					break;
				}
			}
			if(exist)
				continue;
			else
            {
                multiChoices.push_back(res[i].first->data);
                // cout << res[i].first->data << '\n';
				++i;
            }
		}
		else
        {
            multiChoices.push_back(res[i].first->data);
            // cout << res[i].first->data << '\n';
			++i;
        }
	}
	pair result = {res, ques};
    return result;
}

void Dictionary::deleteDict()
{
    trieNode<Word*>* root = trie.getRoot();
    trie.deallocate(root);
    trie.setRoot();
    for(int i = 0; i < words.size(); ++i)
        delete words[i];
    words.clear();
    for(int i = 0; i < allDef.size(); ++i)
        delete allDef[i];
    allDef.clear();
    history.clear();
    trieNode<DefWord*>* defroot = defWords.getRoot();
    defWords.deallocate(defroot);
    defWords.setRoot();
}

void Dictionary::removeWord(const string& str, const string filePath) {
    string file = filePath + "data.txt";
    Word* word;
    bool isExist = trie.findWhole(str, word);
    if (isExist) {
        trie.removeAKey(str);
        std::ifstream fin(file);
        std::string tempFilePath = filePath + "data_removeWord.txt";
        std::ofstream fout(tempFilePath);
        std::string deleteLine = word->data + " ("; 
        std::string line;
        while (getline(fin, line)) {
            long long unsigned int position = line.find(deleteLine);
            if (position == string::npos) fout << line << std::endl;
        }
        fin.close();
        fout.close();
        remove(file.c_str());
        rename(tempFilePath.c_str(), file.c_str());

        fin.open(filePath + "History.txt");

        vector<string> newFile;
        while(getline(fin, line))
        {
            if(line != word->data && line != "")
                newFile.push_back(line);
        }
        fin.close();
        
        fout.open(filePath + "History.txt");
        if (newFile.size() > 100)
            newFile[0] = "";
        for(string s : newFile)
            fout << s << "\n";

        fout.close();

        fin.open(filePath + "FavoriteList.txt");

        newFile.clear();
        while(getline(fin, line))
        {
            if(line != word->data && line != "")
                newFile.push_back(line);
        }
        fin.close();
        
        fout.open(filePath + "FavoriteList.txt");
        if (newFile.size() > 100)
            newFile[0] = "";
        for(string s : newFile)
            fout << s << "\n";

        fout.close();
        return;
    } 
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

void Dictionary::addToFavList(Word* word, const string& fileDir)
{
    word->favourite = true;
    std::ifstream fin;
    std::ofstream fout;
    string line;
    bool insert = true;
    fin.open(fileDir + "FavoriteList.txt");
    while(getline(fin, line))
    {
        if(line == word->data)
            insert = false;
    }
    fin.close();
    if(!insert) return;
    fout.open(fileDir + "FavoriteList.txt", std::ios_base::app);
    fout << word->data << "\n";
    fout.close();
}

void Dictionary::removeFromFavList(Word* word, const string& fileDir)
{
    word->favourite = false;
    
    bool del = false;

    string line;

    ifstream fin;
    vector<string> newFile;
    fin.open(fileDir + "FavoriteList.txt");
    while(getline(fin, line))
    {
        if(line == word->data)
            del = true;
        else
            newFile.push_back(line);
    }
    fin.close();
    if(!del)
        return;
    ofstream fout(fileDir + "FavoriteList.txt");
    for(string s : newFile)
        fout << s << "\n";

    fout.close();
}

vector<Word*> Dictionary::viewFavList(const string& fileDir)
{
    std::ifstream fin(fileDir + "FavoriteList.txt");

    vector<Word*> favList;

    vector<string> words;

    std::string line;
    std::string curWord;

    while(getline(fin, line))
    {

        words.push_back(line);
    }

    for (int i = words.size() - 1; i >= 0; i--)
    {
        Word* newWord;
        trie.findWhole(words[i], newWord);
        favList.push_back(newWord);
    }
    return favList;
}

void Dictionary::addToHis(Word* word, const string& fileDir)
{
    std::ifstream fin;
    std::ofstream fout;
    string line;
    // bool insert = true;

    fin.open(fileDir + "History.txt");

    vector<string> newFile;
    while(getline(fin, line))
    {
        if(line != word->data && line != "")
            newFile.push_back(line);
    }
    fin.close();

    fout.open(fileDir + "History.txt");
    if (newFile.size() > 100)
        newFile[0] = "";
    for(string s : newFile)
        fout << s << "\n";

    fout << word->data;
    fout.close();
    
}

vector<Word*> Dictionary::getHis(const string& fileDir)
{
    std::ifstream fin(fileDir + "History.txt");

    vector<Word*> his;

    vector<string> words;

    std::string line;
    std::string curWord;

    while(getline(fin, line))
    {

        words.push_back(line);
    }

    for (int i = words.size() - 1; i >= 0; i--)
    {
        Word* newWord;
        if(trie.findWhole(words[i], newWord))
            his.push_back(newWord);
    }
    return his;
}

void Dictionary::resetDictionary() {
    history.clear();
    ifstream in;
    ofstream out;
    in.open("data\\Eng-Eng\\backup.txt");
    out.open("data\\Eng-Eng\\data.txt");
    out << in.rdbuf();
    in.close(); out.close();
    in.open("data\\Eng-Vie\\backup.txt");
    out.open("data\\Eng-Vie\\data.txt");
    out << in.rdbuf();
    in.close(); out.close();
    in.open("data\\Emoji\\backup.txt");
    out.open("data\\Emoji\\data.txt");
    out << in.rdbuf();
    in.close(); out.close();
    in.open("data\\Vie-Eng\\backup.txt");
    out.open("data\\Vie-Eng\\data.txt");
    out << in.rdbuf();
    in.close(); out.close();
    in.open("data\\Slang\\backup.txt");
    out.open("data\\Slang\\data.txt");
    out << in.rdbuf();
    in.close(); out.close();
    deleteDict();
    out.open("data\\Eng-Eng\\FavoriteList.txt", std::ios::trunc);
    out.close();
    out.open("data\\Eng-Vie\\FavoriteList.txt", std::ios::trunc);
    out.close();
    out.open("data\\Vie-Eng\\FavoriteList.txt", std::ios::trunc);
    out.close();
    out.open("data\\Emoji\\FavoriteList.txt", std::ios::trunc);
    out.close();
    out.open("data\\Slang\\FavoriteList.txt", std::ios::trunc);
    out.close();
    out.open("data\\Eng-Eng\\History.txt", std::ios::trunc);
    out.close();
    out.open("data\\Eng-Vie\\History.txt", std::ios::trunc);
    out.close();
    out.open("data\\Vie-Eng\\History.txt", std::ios::trunc);
    out.close();
    out.open("data\\Emoji\\History.txt", std::ios::trunc);
    out.close();
    out.open("data\\Slang\\History.txt", std::ios::trunc);
    out.close();
    loadData("data\\Eng-Eng\\");
}

vector<Word*> Dictionary::randomWord() 
{
    vector<Word*> res;
    Word* ran = words[rand() % words.size()];
    res.push_back(ran);
    return res;
}