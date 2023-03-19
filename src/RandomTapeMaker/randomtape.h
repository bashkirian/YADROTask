#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <random>

// Наполняет пустой файл filename размером N случайными int числами
void populateFile(const std::string& filename, const int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, INT_MAX);
    std::ofstream file(filename, std::ios::trunc);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            int randNum = dis(gen);
            file << randNum << " ";
        }
        file.close();
    } else {
        std::cerr << "Error opening file" << std::endl;
    }
}
