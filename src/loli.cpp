// #include "Dictionary.h"
// #include <Windows.h>

// int main()
// {
//     Dictionary dict;
//     string filePath = "D:\\Project\\CS163-Dictionary\\data\\Eng-Eng.txt";
//     dict.loadData(filePath);

//     string input;
//     cout << "Enter the word: ";
//     getline(cin, input);
//     vector<Word*> result = dict.searchWord(input);

//     int length = result.size();
//     for(int i = 0; i < length; ++i)
//     {
//         if(!result[i])
//             continue;
//         cout << result[i]->data << "\n";
        
//         int numDefs = result[i]->defs.size();
//         for(int j = 0; j < numDefs; j++)
//         {
//             cout << j + 1 << ". " << result[i]->defs[j]->data << "\n";
//         }
//         cout << "\n";
//     }
//     cout << "loli\n";
//     return 0;
// }