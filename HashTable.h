/**
 * @file HashTable.h
 * @brief Объявление класса хэш-таблицы
 *
 * @details Хэш-таблица с полиномиальной хэш-функцией.
 *          Разрешение коллизий методом цепочек (std::list).
 *          Подсчитывает количество коллизий для анализа эффективности.
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>
#include "Teacher.h"

/**
 * @class HashTable
 * @brief Класс хэш-таблицы для хранения преподавателей
 */
class HashTable {
private:
    std::vector<std::list<Teacher>> table; ///< Массив бакетов (цепочек)
    int collisions;    ///< Счётчик коллизий
    int totalInserts;  ///< Общее количество вставок

    /**
     * @brief Полиномиальная хэш-функция
     * @param key Строковый ключ
     * @return Хэш-значение в диапазоне [0, table.size()-1]
     */
    size_t hash(const std::string& key) const;

public:
    /**
     * @brief Конструктор
     * @param size Размер хэш-таблицы (количество бакетов)
     */
    explicit HashTable(size_t size = 10007);

    /**
     * @brief Вставка элемента в хэш-таблицу
     * @param t Вставляемый преподаватель
     */
    void insert(const Teacher& t);
    
    /**
     * @brief Построение таблицы из массива
     * @param data Массив преподавателей
     */
    void build(const std::vector<Teacher>& data);
    
    /**
     * @brief Поиск всех элементов с заданным ключом
     * @param key Искомый ключ
     * @return Вектор найденных преподавателей
     */
    std::vector<Teacher> search(const std::string& key) const;

    /**
     * @brief Возвращает количество коллизий
     * @return Число коллизий
     */
    int getCollisions() const;
    
    /**
     * @brief Возвращает общее количество вставок
     * @return Число вставок
     */
    int getTotalInserts() const;
    
    /**
     * @brief Вычисляет частоту коллизий
     * @return Частота коллизий (0..1)
     */
    double getCollisionRate() const;
};

#endif // HASHTABLE_H
