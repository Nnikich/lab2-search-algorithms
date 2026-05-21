/**
 * @file HashTable.cpp
 * @brief Реализация хэш-таблицы
 */

#include "HashTable.h"
#include <functional>

// Хэш для строки (для поиска)
size_t HashTable::hash(const std::string& key) const {
    size_t h = 0;
    for (char c : key) {
        h = (h * 31) + static_cast<size_t>(c);
    }
    return h % table.size();
}

// Хэш для Teacher (для вставки) - комбинирует все поля
size_t HashTable::hash(const Teacher& t) const {
    size_t h = 0;
    
    // Комбинируем все поля преподавателя
    for (char c : t.fullName) {
        h = (h * 31) + static_cast<size_t>(c);
    }
    for (char c : t.faculty) {
        h = (h * 31) + static_cast<size_t>(c);
    }
    for (char c : t.academicTitle) {
        h = (h * 31) + static_cast<size_t>(c);
    }
    for (char c : t.academicDegree) {
        h = (h * 31) + static_cast<size_t>(c);
    }
    
    return h % table.size();
}

HashTable::HashTable(size_t size)
    : table(size), collisions(0), totalInserts(0) {}

void HashTable::insert(const Teacher& t) {
    size_t idx = hash(t);  // ← использует hash(const Teacher&)
    if (!table[idx].empty()) {
        collisions++;
    }
    totalInserts++;
    table[idx].push_back(t);
}

void HashTable::build(const std::vector<Teacher>& data) {
    collisions = 0;
    totalInserts = 0;
    // Оптимальный размер таблицы: простое число, близкое к 2*n
    size_t newSize = std::max(data.size() * 2, (size_t)10007);
    table.clear();
    table.resize(newSize);
    for (const auto& t : data) {
        insert(t);
    }
}

std::vector<Teacher> HashTable::search(const std::string& key) const {
    size_t idx = hash(key);  // ← использует hash(const string&)
    std::vector<Teacher> results;
    for (const auto& t : table[idx]) {
        if (t.key() == key) {
            results.push_back(t);
        }
    }
    return results;
}

int HashTable::getCollisions() const {
    return collisions;
}

int HashTable::getTotalInserts() const {
    return totalInserts;
}

double HashTable::getCollisionRate() const {
    return totalInserts > 0 ? static_cast<double>(collisions) / totalInserts : 0.0;
}
