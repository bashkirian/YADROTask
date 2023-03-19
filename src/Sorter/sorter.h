#pragma once

#include "../Tape/tape.h"
#include "../Configuration/configuration.h"

// класс для сортировки ленты
#include <string>
#include <memory>
#include <vector>

class TapeSorter {
public:
    TapeSorter(size_t memory_limit) :
        m_memory_limit(memory_limit)
    {}

    void tapesort(std::string input_filename, std::string output_filename, configuration::Configuration new_conf);
private:
    // функция для слияния отсортированных лент в выходную
    std::vector<TapeFile> break_tape(TapeFile& m_input_tape, std::vector<std::string>& sub_tape_filenames);
    void merge_tapes(TapeFile& m_output_tape, std::vector<TapeFile>& sub_tapes);
    std::string create_temporary_file();
    size_t m_memory_limit;
    int m_temporary_file_counter = 0;
};
