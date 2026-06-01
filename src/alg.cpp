// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }

    std::string word;
    char ch;
    int wordCount = 0;

    while (file.get(ch)) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            word += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        } else if (!word.empty()) {
            tree.insert(word);
            wordCount++;
            word.clear();
        }
    }
    if (!word.empty()) {
        tree.insert(word);
        wordCount++;
    }
    file.close();

    std::cout << "Words inserted: " << wordCount << std::endl;
}

void printFreq(BST<std::string>& tree) {
    std::ofstream out("result/freq.txt");
    tree.printFreq(out);
    out.close();
}
