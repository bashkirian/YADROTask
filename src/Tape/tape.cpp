#include "tape.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <algorithm>
#include <queue>

using namespace std;

TapeFile::TapeFile(const TapeFile &other)
{
    this->conf = other.conf;
    
}

TapeFile::TapeFile(string m_filename, configuration::Configuration new_configuration) : conf(new_configuration)
{
    fstream file(m_filename, ios::in | ios::out);
    if (!file.good()) // файла нет, нужно создать
    {
        fstream f(m_filename, ios::out | ios::in | ios::trunc);
        swap(file, f);
    }
    m_file = make_unique<fstream>(move(file));
    m_file->open(m_filename, ios::in | ios::out);
    if (!m_file->is_open())
    {
        throw runtime_error("Could not open m_file: " + m_filename);
    }
}

int TapeFile::read() 
{
    this_thread::sleep_for(chrono::milliseconds(conf.m_read_delay));
    std::streampos oldPos = m_file->tellg();
    int value;
    *(m_file.get()) >> value;
    cout << value << " ";
    m_file->seekg(oldPos);
    return value;
}

void TapeFile::write(int value) 
{
    this_thread::sleep_for(chrono::milliseconds(conf.m_write_delay));
    *(m_file.get()) << value << " ";
}

void TapeFile::rewind() 
{
    this_thread::sleep_for(chrono::milliseconds(conf.m_rewind_delay));
    m_file->seekg(0);
}

void TapeFile::shift(int offset) 
{
    this_thread::sleep_for(chrono::milliseconds(conf.m_shift_delay * offset));
    for (int i = 0; i < offset; ++i)
    {
        int value;
        *(m_file.get()) >> value;
    }
}

configuration::Configuration TapeFile::getConfiguration() 
{
    return conf;
}

bool TapeFile::isended() 
{
    return m_file->eof();
}