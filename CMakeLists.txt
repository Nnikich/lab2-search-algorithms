cmake_minimum_required(VERSION 3.10)
project(Lab2_Search)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Все исходники
set(SOURCES
    main.cpp
    Teacher.cpp
    LinearSearch.cpp
    BSTree.cpp
    RBTree.cpp
    HashTable.cpp
)

add_executable(search_test ${SOURCES})
