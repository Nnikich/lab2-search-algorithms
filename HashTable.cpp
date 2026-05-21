/**
 * @file HashTable.cpp
 * @brief Реализация хэш-таблицы
 */

#include "HashTable.h"

size_t HashTable::hash(const std::string& key) const {
    size_t h = 0;
    for (char c : key) {
        h = (h * 31) + static_cast<size_t>(c);
    }
    return h % table.size();
}

HashTable::HashTable(size_t size)
    : table(size), collisions(0), totalInserts(0) {}

void HashTable::insert(const Teacher& t) {
    size_t idx = hash(t.key());
    if (!table[idx].empty()) {
        collisions++;
    }
    totalInserts++;
    table[idx].push_back(t);
}

void HashTable::build(const std::vector<Teacher>& data) {
    collisions = 0;
    totalInserts = 0;
    for (const auto& t : data) {
        insert(t);
    }
}

std::vector<Teacher> HashTable::search(const std::string& key) const {
    size_t idx = hash(key);
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
