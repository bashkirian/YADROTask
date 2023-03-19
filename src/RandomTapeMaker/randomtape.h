/**
 * @file randomtape.h
 * @brief Хедер для наполнения пустого файла целыми числами случайным образом
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <random>

/**
 * @brief Наполняет пустой файл случайными числами
 * 
 * @param filename Имя файла для популяции
 * @param N Количество чисел в итоговом файле
 */
void populateFile(const std::string& filename, const int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, INT_MAX);
    std::ofstream file(filename, std::ios::trunc);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            int randNum = dis(gen);
            file << " " << randNum;
        }
        file.close();
    } else {
        std::cerr << "Error opening file" << std::endl;
    }
}
