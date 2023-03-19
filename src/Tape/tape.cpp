#include "tape.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * @brief Construct a new Tape File:: Tape File object
 *
 * @param other 
 */
TapeFile::TapeFile(const TapeFile &other)
{
    this->filename = other.filename;
    this->conf = other.conf;
}

/**
 * @brief Construct a new Tape File:: Tape File object
 * 
 * @param m_filename 
 * @param new_configuration 
 */
TapeFile::TapeFile(string m_filename, configuration::Configuration new_configuration) : filename(m_filename), conf(new_configuration)
{
    fstream m_file(m_filename, ios::in | ios::out);
    m_file.open(m_filename, ios::in | ios::out);
    if (!m_file.is_open())
    {
        throw runtime_error("Could not open m_file: " + m_filename);
    }
}

/**
 * @brief Проверить, открыт ли файл
 * 
 * @return true 
 * @return false 
 */
bool TapeFile::isOpen()
{
    return m_file.is_open();
}

/**
 * @brief Открыть файл
 * 
 */
void TapeFile::toOpen()
{
    m_file.open(filename, ios::in | ios::out);
}

/**
 * @brief Прочитать значение под головкой
 * 
 * @return int 
 */
int TapeFile::read() 
{
    this_thread::sleep_for(chrono::milliseconds(conf.m_read_delay));
    std::streampos oldPos = m_file.tellg();
    int value;
    m_file >> value;
    m_file.seekg(oldPos);
    return value;
}

void TapeFile::write(int value) 
{
    this_thread::sleep_for(chrono::milliseconds(conf.m_write_delay));
    if (filename == "output.txt")
    {
        fstream fs;
        fs.open("output.txt", ios::out | ios::trunc);
        fs << " " << value;
    }
    m_file << " " << value;
}

/**
 * @brief Переместить головку в начало ленты
 * 
 */
void TapeFile::rewind() 
{
    this_thread::sleep_for(chrono::milliseconds(conf.m_rewind_delay));
    m_file.seekg(0);
}

/**
 * @brief Переместить головку на offset позиций вперед
 * 
 * @param offset 
 */
void TapeFile::shift(int offset) 
{
    this_thread::sleep_for(chrono::milliseconds(conf.m_shift_delay * offset));
    for (int i = 0; i < offset; ++i)
    {
        int value;
        m_file >> value;
    }
}

/**
 * @brief Вернуть конфигурацию ленты
 * 
 * @return configuration::Configuration 
 */
configuration::Configuration TapeFile::getConfiguration() 
{
    return conf;
}

/**
 * @brief Достигнут ли конец файла
 * 
 * @return true 
 * @return false 
 */
bool TapeFile::isended() 
{
    return m_file.eof();
}