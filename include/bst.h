// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;

  Node* insert(Node* node, T value) {
    if (!node) return new Node(value);
    if (value == node->key) {
      node->count++;
    } else if (value < node->key) {
      node->left = insert(node->left, value);
    } else {
      node->right = insert(node->right, value);
    }
    return node;
  }

  int depth(Node* node) const {
    if (!node) return -1;
    int l = depth(node->left);
    int r = depth(node->right);
    return 1 + std::max(l, r);
  }

  Node* search(Node* node, T value) const {
    if (!node) return nullptr;
    if (value == node->key) return node;
    if (value < node->key) return search(node->left, value);
    return search(node->right, value);
  }

  void delTree(Node* node) {
    if (node) {
      delTree(node->left);
      delTree(node->right);
      delete node;
    }
  }

  void collectNodes(Node* node,
                    std::vector<std::pair<T, int>>& out) const {
    if (node) {
      collectNodes(node->left, out);
      out.emplace_back(node->key, node->count);
      collectNodes(node->right, out);
    }
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { delTree(root); }

  void insert(T value) { root = insert(root, value); }

  int depth() const { return depth(root); }

  int search(T value) const {
    Node* found = search(root, value);
    return found ? found->count : 0;
  }

  void printFreq(std::ostream& out = std::cout) const {
    std::vector<std::pair<T, int>> freq;
    collectNodes(root, freq);
    std::sort(freq.begin(), freq.end(),
      [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
        return a.second > b.second;
      });
    int rank = 1;
    for (const auto& p : freq) {
      out << rank << "    " << p.first << ": " << p.second << "\n";
      rank++;
    }
  }
};

// Глобальные функции (НЕ внутри класса)
void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) return;
  std::string word;
  char ch;
  while (file.get(ch)) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == '\'')) {
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

#endif  // INCLUDE_BST_H_
