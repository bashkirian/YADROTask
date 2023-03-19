#include <string>
#include <iostream>

#include "./Configuration/configuration.h" // класс конфигурации
#include "./Configuration/conf_reader.h" // чтение конфигурации
#include "./Tape/tape.h" // лента
#include "./Sorter/sorter.h" // сортировщик

using namespace std;

struct Configurations
{
    int rewind_delay; // задержка перемотки
    int shift_delay; // задержка движения на одну позицию
    int read_delay; // задержка чтения
    int write_delay; // задержка записывания 
};

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }


    string input_filename = argv[1];
    string output_filename = argv[2];
    try {
        int M = 10; // количество памяти, выделенное под ленты
        configuration::Configuration new_configuration;
        configuration::configurations_map cm = configuration::ReadConfigurations();
        new_configuration.m_read_delay = stoi(cm["Tape"]["ReadDelay"]);
        new_configuration.m_write_delay = stoi(cm["Tape"]["WriteDelay"]);
        new_configuration.m_shift_delay = stoi(cm["Tape"]["ShiftDelay"]);
        new_configuration.m_rewind_delay = stoi(cm["Tape"]["RewindDelay"]);
        TapeSorter sorter(M);
        sorter.tapesort(input_filename, output_filename, new_configuration);
    } 
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}