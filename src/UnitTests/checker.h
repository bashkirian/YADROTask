#pragma once
#include <iostream>
#include <fstream>

// проверка на сортированность файла без использования доп.памяти
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
