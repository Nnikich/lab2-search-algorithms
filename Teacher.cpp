/**
 * @file Teacher.cpp
 * @brief Реализация структуры Teacher
 */

#include "Teacher.h"

Teacher::Teacher(const std::string& name, const std::string& fac,
                 const std::string& title, const std::string& degree)
    : fullName(name), faculty(fac), academicTitle(title), academicDegree(degree) {}

std::string Teacher::key() const {
    return fullName;
}

bool Teacher::operator<(const Teacher& other) const {
    return fullName < other.fullName;
}

bool Teacher::operator>(const Teacher& other) const {
    return fullName > other.fullName;
}

bool Teacher::operator==(const Teacher& other) const {
    return fullName == other.fullName;
}
