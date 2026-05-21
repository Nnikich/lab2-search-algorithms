/**
 * @file LinearSearch.h
 * @brief Объявление класса линейного поиска
 *
 * @details Алгоритм последовательно перебирает все элементы массива
 *          и возвращает индексы всех элементов, ключ которых совпадает с искомым.
 * @complexity O(n)
 */

#ifndef LINEAR_SEARCH_H
#define LINEAR_SEARCH_H

#include <vector>
#include <string>
#include "Teacher.h"

/**
 * @class LinearSearch
 * @brief Класс для выполнения линейного поиска
 *
 * Содержит статический метод search, который находит все вхождения
 * элемента по ключу в массиве преподавателей.
 */
class LinearSearch {
public:
    /**
     * @brief Выполняет линейный поиск всех элементов с заданным ключом
     * @param data Массив преподавателей
     * @param key Искомый ключ (ФИО)
     * @return Вектор индексов элементов, соответствующих ключу
     */
    static std::vector<int> search(const std::vector<Teacher>& data, const std::string& key);
};

#endif // LINEAR_SEARCH_H
