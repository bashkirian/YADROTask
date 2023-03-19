#include <string>
#include <iostream>
#include <random>
#include <ctime>

#include "test_runner.h"                    // юнит-тесты
#include "profiler.h"                       // профилирование
#include "checker.h"                        // проверка на сортированность
#include "../Configuration/configuration.h" // определение класса конфигурации
#include "../Configuration/conf_reader.h"   // чтение конфигурации
#include "../RandomTapeMaker/randomtape.h"  // создание случайной ленты
#include "../Tape/tape.h"                   // ленты
#include "../Sorter/sorter.h"               // сортировщик
using namespace std;

struct Configurations
{
    int rewind_delay; // задержка перемотки
    int shift_delay;  // задержка движения на одну позицию
    int read_delay;   // задержка чтения
    int write_delay;  // задержка записывания
};

configuration::Configuration new_configuration;
TestRunner tr;
string input_filename;
string output_filename;

bool SortAndCheck(int N, int M)
{
    populateFile(input_filename, N);
    TapeFile input_tape(input_filename, new_configuration);
    TapeFile output_tape(output_filename, new_configuration);
    TapeSorter sorter(M);
    sorter.tapesort(input_filename, output_filename, new_configuration);
    return (isFileSorted(output_filename));
}

void TestFit()
{
    srand(time(nullptr));
    int N = rand() % 100 + 1;
    int M = N * 2;
    ASSERT(SortAndCheck(N, M));
}

void TestNotFit()
{
    srand(time(nullptr));
    int N = rand() % 100 + 1;
    int M = N / (rand() % 5 + 1);
    ASSERT(SortAndCheck(N, M));
}

void TestBigFit()
{
    srand(time(nullptr));
    int N = rand() % 10000 + 1;
    int M = N * 2;
    ASSERT(SortAndCheck(N, M));
}

void TestBigNotFit()
{
    srand(time(nullptr));
    int N = rand() % 10000 + 1;
    int M = N / (rand() % 5 + 1);
    ASSERT(SortAndCheck(N, M));
}

void RunTests()
{
    {
        LOG_DURATION("Tests with small tape that fits into memory");
        RUN_TEST(tr, TestFit);
    }
    {
        LOG_DURATION("Tests with small tape that doesn't fit into memory");
        RUN_TEST(tr, TestNotFit);
    }
    {
        LOG_DURATION("Tests with big tape that fits into memory");
        RUN_TEST(tr, TestBigFit);
    }
    {
        LOG_DURATION("Tests with big tape that doesn't fit into memory");
        RUN_TEST(tr, TestBigNotFit);
    }
}

int main(int argc, char **argv)
{

    configuration::configurations_map cm = configuration::ReadConfigurations();
    new_configuration.m_read_delay = stoi(cm["Tape"]["ReadDelay"]);
    new_configuration.m_write_delay = stoi(cm["Tape"]["WriteDelay"]);
    new_configuration.m_shift_delay = stoi(cm["Tape"]["ShiftDelay"]);
    new_configuration.m_rewind_delay = stoi(cm["Tape"]["RewindDelay"]);

    input_filename = "TestIO/input.txt";
    output_filename = "TestIO/output.txt";
    {
        LOG_DURATION("Total Test Time")
        RunTests();
    }
    return 0;
}