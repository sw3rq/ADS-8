// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

int main() {
    BST<std::string> words;

    makeTree(words, "C:/Users/Admin/source/repos/LabBST/x64/Debug/war_peace.txt");

    std::cout << "Tree height: " << words.depth() << "\n";
    std::cout << "Search 'the': " << words.search("the") << "\n";
    std::cout << "Search 'pierre': " << words.search("pierre") << "\n";

    printFreq(words);

    std::cout << "\nDone! Check result/freq.txt\n";

    return 0;
}
