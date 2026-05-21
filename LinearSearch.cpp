/**
 * @file LinearSearch.cpp
 * @brief Реализация линейного поиска
 */

#include "LinearSearch.h"

std::vector<int> LinearSearch::search(const std::vector<Teacher>& data, const std::string& key) {
    std::vector<int> results;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].key() == key) {
            results.push_back(static_cast<int>(i));
        }
    }
    return results;
}

