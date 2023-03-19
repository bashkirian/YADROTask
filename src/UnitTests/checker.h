#pragma once
#include <iostream>
#include <fstream>

/**
 * @brief Проверка на сортированность файла без использования доп.памяти
 * 
 * @param filename 
 * @return true 
 * @return false 
 */
bool isFileSorted(const std::string& filename) {
    std::ifstream file(filename);
    int previousNumber, currentNumber;
    file >> previousNumber;
    while (file >> currentNumber) {
        if (currentNumber < previousNumber) {
            file.close();
            return false;
        }
        previousNumber = currentNumber;
    }
    file.close();
    return true;
}
