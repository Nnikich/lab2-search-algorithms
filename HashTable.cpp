/**
 * @file HashTable.cpp
 * @brief Реализация хэш-таблицы
 */

#include "HashTable.h"
#include <functional>

// Вспомогательная функция для поиска следующего простого числа
static size_t getNextPrime(size_t n) {
    if (n < 2) return 2;
    while (true) {
        bool isPrime = true;
        for (size_t i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) return n;
        ++n;
    }
}

// Хэш для строки (для поиска)
size_t HashTable::hash(const std::string& key) const {
    size_t h = 0;
    for (char c : key) {
        // Важно: кастим к unsigned char для предотвращения знакового расширения UTF-8 русских букв
        h = (h * 31) + static_cast<size_t>(static_cast<unsigned char>(c));
    }
    return h % table.size();
}

// Хэш для Teacher (для вставки) - использует только ключ
size_t HashTable::hash(const Teacher& t) const {
    return hash(t.key());
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
    // Оптимальный размер таблицы: простое число, близкое к 3*n (снижает load factor до 0.33)
    size_t newSize = getNextPrime(std::max(data.size() * 3, (size_t)10007));
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
