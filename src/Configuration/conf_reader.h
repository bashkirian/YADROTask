#pragma once 

#include <iostream>
#include <fstream>
#include <string>
#include <map>


namespace configuration
{
    using configurations_map = std::map<std::string, std::map<std::string, std::string>>;

    configurations_map ReadConfigurations()
    {
        std::string filename = "config.cfg";

        std::ifstream file;
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file with configurations " + filename);
        }

        std::map<std::string, std::map<std::string, std::string>> sections;
        std::string current_section;

        std::string line;
        while (std::getline(file, line)) {
            // Игнорируем комментарии и пустые строки
            if (line.empty() || line[0] == '#' || line[0] == ';') {
                continue;
            }

            // Проверяем, секция или нет
            if (line[0] == '[' && line[line.size()-1] == ']') {
                current_section = line.substr(1, line.size()-2);
            }
            else {
                // Парсинг имени параметра и его значения
                size_t delimiter_pos = line.find('=');
                if (delimiter_pos == std::string::npos) {
                    throw std::logic_error("Invalid configuration parameter: " + line);
                }

                std::string name = line.substr(0, delimiter_pos - 1);
                std::string value = line.substr(delimiter_pos + 2);
                // Сохраняем параметр в текущей секции
                sections[current_section][name] = value;
            }
        }
        return sections;
    }
}