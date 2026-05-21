/**
 * @file BSTree.cpp
 * @brief Реализация бинарного дерева поиска
 */

#include "BSTree.h"

BSTree::Node::Node(const Teacher& t) : data(t), left(nullptr), right(nullptr) {}

BSTree::BSTree() : root(nullptr) {}

BSTree::~BSTree() {
    clear(root);
}

void BSTree::insert(Node*& node, const Teacher& t) {
    if (!node) {
        node = new Node(t);
        return;
    }
    if (t.key() < node->data.key())
        insert(node->left, t);
    else
        insert(node->right, t);
}

void BSTree::search(Node* node, const std::string& key, std::vector<Teacher>& results) const {
    if (!node) return;
    if (key < node->data.key())
        search(node->left, key, results);
    else if (key > node->data.key())
        search(node->right, key, results);
    else {
        results.push_back(node->data);
        search(node->right, key, results);
    }
}

void BSTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void BSTree::insert(const Teacher& t) {
    insert(root, t);
}

void BSTree::build(const std::vector<Teacher>& data) {
    for (const auto& t : data) {
        insert(t);
    }
}

std::vector<Teacher> BSTree::search(const std::string& key) const {
    std::vector<Teacher> results;
    search(root, key, results);
    return results;
}
