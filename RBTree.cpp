/**
 * @file RBTree.cpp
 * @brief Реализация красно-черного дерева
 */

#include "RBTree.h"

RBTree::Node::Node(const Teacher& t)
    : data(t), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}

RBTree::RBTree() : root(nullptr) {}

RBTree::~RBTree() {
    clear(root);
}

void RBTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
}

void RBTree::fixInsert(Node* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::insert(Node*& node, Node* parent, const Teacher& t) {
    if (!node) {
        node = new Node(t);
        node->parent = parent;
        fixInsert(node);
        return;
    }
    if (t.key() < node->data.key())
        insert(node->left, node, t);
    else
        insert(node->right, node, t);
}

void RBTree::search(Node* node, const std::string& key, std::vector<Teacher>& results) const {
    if (!node) return;
    if (key < node->data.key())
        search(node->left, key, results);
    else if (key > node->data.key())
        search(node->right, key, results);
    else {
        results.push_back(node->data);
        search(node->left, key, results);
        search(node->right, key, results);
    }
}

void RBTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void RBTree::insert(const Teacher& t) {
    insert(root, nullptr, t);
}

void RBTree::build(const std::vector<Teacher>& data) {
    for (const auto& t : data) {
        insert(t);
    }
}

std::vector<Teacher> RBTree::search(const std::string& key) const {
    std::vector<Teacher> results;
    search(root, key, results);
    return results;
}


