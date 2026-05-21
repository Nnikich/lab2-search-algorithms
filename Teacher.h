/**
 * @file Teacher.h
 * @brief Определение структуры данных "Преподаватель"
 * @version 2.0
 * @date 2026-05-21
 *
 * @details Данный файл содержит объявление структуры Teacher,
 *          которая используется в лабораторных работах №1 и №2.
 *          В ЛР2 ключом поиска является поле fullName.
 */

#ifndef TEACHER_H
#define TEACHER_H

#include <string>

/**
 * @struct Teacher
 * @brief Структура, представляющая преподавателя
 *
 * Содержит полную информацию о преподавателе:
 * - ФИО (fullName) — используется как ключ для поиска в ЛР2
 * - Факультет (faculty)
 * - Учёное звание (academicTitle)
 * - Учёная степень (academicDegree)
 */
struct Teacher {
    std::string fullName;      ///< ФИО преподавателя (ключ для поиска)
    std::string faculty;       ///< Факультет
    std::string academicTitle; ///< Учёное звание
    std::string academicDegree;///< Учёная степень

    /**
     * @brief Конструктор по умолчанию
     */
    Teacher() = default;
    
    /**
     * @brief Конструктор с параметрами
     * @param name ФИО преподавателя
     * @param fac Факультет
     * @param title Учёное звание
     * @param degree Учёная степень
     */
    Teacher(const std::string& name, const std::string& fac,
            const std::string& title, const std::string& degree);

    /**
     * @brief Возвращает ключ для поиска (первое не числовое поле)
     * @return ФИО преподавателя
     */
    std::string key() const;

    // Операторы сравнения для деревьев поиска
    /**
     * @brief Оператор меньше
     * @param other Другой преподаватель
     * @return true если ФИО текущего меньше ФИО другого
     */
    bool operator<(const Teacher& other) const;
    
    /**
     * @brief Оператор больше
     * @param other Другой преподаватель
     * @return true если ФИО текущего больше ФИО другого
     */
    bool operator>(const Teacher& other) const;
    
    /**
     * @brief Оператор равенства
     * @param other Другой преподаватель
     * @return true если ФИО совпадают
     */
    bool operator==(const Teacher& other) const;
};

#endif // TEACHER_H
