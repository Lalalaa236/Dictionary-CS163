#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Definition {
    std::string wordType;
    std::string meanings;
};

struct Word {
    std::string word;
    std::vector<Definition> definitions;
};

int main() {
    std::ifstream inFile("C:\\Users\\Hisokaxxzk\\Downloads\\Vi-Eng.txt");
    std::ofstream outFile("output.txt");
    std::string line;
    Word word;
    Definition def;
    bool isfirst = true;

    while (std::getline(inFile, line)) {
        if (line[0] == '@') {
            if (!word.word.empty()) {
                word.definitions.push_back(def);
                for (const auto &def : word.definitions) {
                    outFile << word.word << " (" << def.wordType << ") " << def.meanings << "\n";
                }
            }
            std::istringstream iss(line.substr(1));
            size_t pos = line.find('/');
            word.word = line.substr(1, pos - 1);
            word.definitions.clear();
            def.meanings.clear();
            isfirst = true;
        } 
        else if (line[0] == '*') {
            if (!def.meanings.empty()) {
                word.definitions.push_back(def);
            }
            def.wordType = line.substr(line.find(' ') + 1);
            def.meanings.clear();
            isfirst = true;
        } else if (line[0] == '-') {
            if (isfirst) {
                def.meanings += line.substr(2);
                isfirst = false;
            }
        }
    }

    if (!word.word.empty()) {
        word.definitions.push_back(def);
        for (const auto &def : word.definitions) {
            outFile << word.word << " (" << def.wordType << ") " << def.meanings << "\n";
        }
    }

    inFile.close();
    outFile.close();
    return 0;
}
