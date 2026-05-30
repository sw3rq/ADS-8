// Copyright 2021 NNTU-CS
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) return;
  std::string word;
  char ch;
  while (file.get(ch)) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
      word += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }
  if (!word.empty())
    tree.insert(word);
  file.close();
}

void printFreq(BST<std::string>& tree) {
  tree.printFreq(std::cout);
  std::ofstream out("result/freq.txt");
  if (out) {
    tree.printFreq(out);
    out.close();
  }
}
