// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> words;
    makeTree(words, "src/war_peace.txt");

    std::cout << "Tree height: " << words.depth() << "\n";
    std::cout << "Search 'the': " << words.search("the") << "\n";
    std::cout << "Search 'pierre': " << words.search("pierre") << "\n";

    printFreq(words);

    std::cout << "\nDone! Check result/freq.txt\n";

    return 0;
}
