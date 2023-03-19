#pragma once

#include "../Tape/tape.h"
#include "../Configuration/configuration.h"

#include <string>
#include <memory>
#include <vector>

/**
 * @brief Класс для сортировки ленты
 */
class TapeSorter {
public:
    /**
     * @brief Construct a new Tape Sorter object
     * 
     * @param memory_limit RAM
     */
    TapeSorter(size_t memory_limit) :
        m_memory_limit(memory_limit)
    {}

    /**
     * @brief Основная функция для сортировки ленты
     * 
     * @param input_filename Имя входного файла-ленты
     * @param output_filename Имя выходного файла-ленты
     * @param new_conf Конфигурация ленты
     */
    void tapesort(std::string input_filename, std::string output_filename, configuration::Configuration new_conf);
private:
    /**
     * @brief Разбить ленту на части, помещающиеся в выделенной памяти
     * 
     * @param m_input_tape входная лента 
     * @param sub_tape_filenames имена под-лент
     * @return std::vector<TapeFile> 
     */
    std::vector<TapeFile> break_tape(TapeFile& m_input_tape, std::vector<std::string>& sub_tape_filenames);
    /**
     * @brief Слияние отсортированных лент
     * 
     * @param m_output_tape выходная лента
     * @param sub_tapes под-ленты
     */
    void merge_tapes(TapeFile& m_output_tape, std::vector<TapeFile>& sub_tapes);
    /**
     * @brief Создание временной под-ленты
     * 
     * @return std::string 
     */
    std::string create_temporary_file();
    size_t m_memory_limit;
    int m_temporary_file_counter = 0;
};
