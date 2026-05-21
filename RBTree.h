/**
 * @file RBTree.h
 * @brief Объявление класса красно-черного дерева
 *
 * @details Сбалансированное бинарное дерево поиска с гарантированной
 *          сложностью O(log n) для всех операций.
 * @complexity O(log n) всегда
 */

#ifndef RBTREE_H
#define RBTREE_H

#include <vector>
#include <string>
#include "Teacher.h"

/**
 * @enum Color
 * @brief Цвет узла красно-черного дерева
 */
enum Color { RED, BLACK };

/**
 * @class RBTree
 * @brief Класс красно-черного дерева
 */
class RBTree {
private:
    /**
     * @struct Node
     * @brief Узел красно-черного дерева
     */
    struct Node {
        Teacher data;   ///< Данные преподавателя
        Node* left;     ///< Левый потомок
        Node* right;    ///< Правый потомок
        Node* parent;   ///< Родительский узел
        Color color;    ///< Цвет узла
        
        /**
         * @brief Конструктор узла
         * @param t Данные преподавателя
         */
        explicit Node(const Teacher& t);
    };
    
    Node* root; ///< Корень дерева

    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void fixInsert(Node* z);
    void insert(Node*& node, Node* parent, const Teacher& t);
    void search(Node* node, const std::string& key, std::vector<Teacher>& results) const;
    void clear(Node* node);

public:
    RBTree();
    ~RBTree();
    void insert(const Teacher& t);
    void build(const std::vector<Teacher>& data);
    std::vector<Teacher> search(const std::string& key) const;
};

#endif // RBTREE_H
