/**
 * @file main.cpp
 * @brief Главный модуль лабораторной работы №2
 * @version 2.0
 * @date 2026-05-21
 *
 * @details Программа сравнивает эффективность различных алгоритмов поиска:
 *          - Линейный поиск (O(n))
 *          - Бинарное дерево поиска (BST) (O(log n) в среднем)
 *          - Красно-черное дерево (RBT) (O(log n) всегда)
 *          - Хэш-таблица (O(1) в среднем)
 *          - std::multimap (O(log n))
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <random>
#include <map>
#include "Teacher.h"
#include "LinearSearch.h"
#include "BSTree.h"
#include "RBTree.h"
#include "HashTable.h"

using namespace std;
using namespace chrono;

// Загрузка данных из CSV
vector<Teacher> loadFromCSV(const string& filename) {
    vector<Teacher> result;
    ifstream file(filename);
    if (!file.is_open()) return result;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string name, faculty, title, degree;
        getline(ss, name, ',');
        getline(ss, faculty, ',');
        getline(ss, title, ',');
        getline(ss, degree, ',');
        result.emplace_back(name, faculty, title, degree);
    }
    return result;
}

// Измерение времени для структур с методом search
template<typename Structure>
double measureSearchTime(Structure& structure, const string& key, int repeatCount = 100) {
    auto start = high_resolution_clock::now();
    volatile size_t prevent_opt = 0;
    for (int i = 0; i < repeatCount; ++i) {
        auto res = structure.search(key);
        prevent_opt += res.size();
    }
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count() / repeatCount;
}

// Специализация для линейного поиска
double measureLinearSearchTime(const vector<Teacher>& data, const string& key, int repeatCount = 100) {
    auto start = high_resolution_clock::now();
    volatile size_t prevent_opt = 0;
    for (int i = 0; i < repeatCount; ++i) {
        auto res = LinearSearch::search(data, key);
        prevent_opt += res.size();
    }
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count() / repeatCount;
}

size_t nextPrime(size_t n) {
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

int main() {
    vector<size_t> sizes = {100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000};
    string dataDir = "../data";
    
    system("mkdir -p results");
    
    ofstream out("results/times.csv");
    out << "Size,LinearSearch,BSTree,RBTree,HashTable,StdMultimap\n";
    
    ofstream collOut("results/collisions.csv");
    collOut << "Size,Collisions,TotalInserts,CollisionRate\n";
    
    for (size_t n : sizes) {
        string filename = dataDir + "/data_" + to_string(n) + ".csv";
        vector<Teacher> data = loadFromCSV(filename);
        if (data.empty()) {
            cerr << "Пропускаем size=" << n << ", файл не найден: " << filename << endl;
            continue;
        }
        
        cout << "Testing size: " << n << endl;
        
        // Выбираем случайный ключ
        string searchKey = data[0].key();
        
        // 1. Линейный поиск
        double tLinear = measureLinearSearchTime(data, searchKey);
        
        // 2. BST
        BSTree bst;
        bst.build(data);
        double tBST = measureSearchTime(bst, searchKey);
        
        // 3. RBTree
        RBTree rbt;
        rbt.build(data);
        double tRBT = measureSearchTime(rbt, searchKey);
        
        // 4. HashTable
        size_t tableSize = nextPrime(data.size() * 2);
        HashTable ht(tableSize);
        ht.build(data);
        double tHash = measureSearchTime(ht, searchKey);
        collOut << n << "," << ht.getCollisions() << ","
                << ht.getTotalInserts() << "," << ht.getCollisionRate() << "\n";
        
        // 5. std::multimap
        multimap<string, Teacher> mmap;
        for (const auto& t : data) {
            mmap.insert({t.key(), t});
        }
        auto start = high_resolution_clock::now();
        volatile size_t prevent_opt = 0;
        for (int i = 0; i < 100; ++i) {
            auto range = mmap.equal_range(searchKey);
            prevent_opt += std::distance(range.first, range.second);
        }
        auto end = high_resolution_clock::now();
        double tMultimap = duration<double>(end - start).count() / 100;
        
        out << n << "," << tLinear << "," << tBST << "," << tRBT << "," << tHash << "," << tMultimap << "\n";
        out.flush();
        collOut.flush();
        
        cout << "   Linear: " << tLinear << "s, BST: " << tBST << "s, RBT: " << tRBT
             << "s, Hash: " << tHash << "s, multimap: " << tMultimap << "s\n";
    }
    
    out.close();
    collOut.close();
    
    cout << "\nЗамеры завершены!\n";
    cout << "Результаты: results/times.csv\n";
    cout << "Коллизии: results/collisions.csv\n";
    
    return 0;
}
