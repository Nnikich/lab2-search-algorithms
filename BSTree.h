/**
 * @file BSTree.h
 * @brief Объявление класса бинарного дерева поиска
 *
 * @details Простое бинарное дерево поиска без балансировки.
 *          Поддерживает вставку и поиск всех элементов с заданным ключом.
 * @warning В худшем случае (отсортированные данные) деградирует до O(n)
 */

#ifndef BSTREE_H
#define BSTREE_H

#include <vector>
#include <string>
#include "Teacher.h"

/**
 * @class BSTree
 * @brief Класс бинарного дерева поиска
 *
 * Хранит объекты Teacher, упорядоченные по ключу (fullName).
 * Позволяет находить все объекты с одинаковым ключом.
 */
class BSTree {
private:
    /**
     * @struct Node
     * @brief Внутренняя структура узла дерева
     */
    struct Node {
        Teacher data;   ///< Данные преподавателя
        Node* left;     ///< Левый потомок
        Node* right;    ///< Правый потомок
        
        /**
         * @brief Конструктор узла
         * @param t Данные преподавателя
         */
        explicit Node(const Teacher& t);
    };
    
    Node* root; ///< Корень дерева

    /**
     * @brief Рекурсивная вставка элемента
     * @param node Текущий узел (передаётся по ссылке для изменения)
     * @param t Вставляемый преподаватель
     */
    void insert(Node*& node, const Teacher& t);

    /**
     * @brief Рекурсивный поиск всех вхождений
     * @param node Текущий узел
     * @param key Искомый ключ
     * @param results Вектор для сбора результатов
     */
    void search(Node* node, const std::string& key, std::vector<Teacher>& results) const;

    /**
     * @brief Рекурсивное удаление всех узлов
     * @param node Текущий узел
     */
    void clear(Node* node);

public:
    /**
     * @brief Конструктор
     */
    BSTree();
    
    /**
     * @brief Деструктор
     */
    ~BSTree();

    /**
     * @brief Вставка элемента в дерево
     * @param t Вставляемый преподаватель
     */
    void insert(const Teacher& t);
    
    /**
     * @brief Построение дерева из массива
     * @param data Массив преподавателей
     */
    void build(const std::vector<Teacher>& data);

    /**
     * @brief Поиск всех элементов с заданным ключом
     * @param key Искомый ключ (ФИО)
     * @return Вектор найденных преподавателей
     */
    std::vector<Teacher> search(const std::string& key) const;
};

#endif // BSTREE_H

