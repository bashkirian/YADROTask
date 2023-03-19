#include <string>
#include <iostream>
#include <random>
#include <ctime>

#include "test_runner.h"                   // юнит-тесты
#include "configuration.h"                 // определение класса конфигурации
#include "conf_reader.h"                   // чтение конфигурации
#include "checker.h"                       // проверка на сортированность
#include "profiler.h"                      // профилирование
#include "../RandomTapeMaker/randomtape.h" // создание случайной ленты

using namespace std;

struct Configurations
{
    int rewind_delay; // задержка перемотки
    int shift_delay;  // задержка движения на одну позицию
    int read_delay;   // задержка чтения
    int write_delay;  // задержка записывания
};

class UnitTester
{
private:
    configuration::Configuration new_configuration;
    TestRunner tr;
    string input_filename;
    string output_filename;

    // N - Максимальная память под ленту
    // M - Максимальная память RAM
    bool SortAndCheck(int N, int M)
    {
        populateFile(input_filename, N);
        TapeFile input_tape(input_filename, new_configuration);
        TapeFile output_tape(output_filename, new_configuration);
        TapeSorter sorter(input_tape, output_tape, M);
        sorter.sorttapes();
        return (isFileSorted(output_filename));
    }
    bool TestFit()
    {
        srand(time(nullptr));
        for (int i = 0; i < 10; ++i)
        {
            int N = rand() % 1000 + 1;
            int M = rand() % N + 1;
            SortAndCheck(N, M);
        }
    }

    bool TestNotFit()
    {
        srand(time(nullptr));
        for (int i = 1; i <= 10; ++i)
        {
            int N = rand() % 1000 + 1;
            int M = N / (rand() % i + 1);
            SortAndCheck(N, M);
        }
    }

    bool TestBigFit()
    {
        srand(time(nullptr));
        for (int i = 0; i < 10; ++i)
        {
            int N = rand() % 100000000 + 1;
            int M = rand() % N + 1;
            SortAndCheck(N, M);
        }
    }

    bool TestBigNotFit()
    {
        srand(time(nullptr));
        for (int i = 1; i <= 10; ++i)
        {
            int N = rand() % 1000 + 1;
            int M = N / (rand() % i + 1);
            SortAndCheck(N, M);
        }
    }

public:
    UnitTester(string _if, string _of) : input_filename(_if), output_filename(_of)
    {
        configuration::configurations_map cm = configuration::ReadConfigurations();
        new_configuration.m_read_delay = stoi(cm["Tape"]["ReadDelay"]);
        new_configuration.m_write_delay = stoi(cm["Tape"]["WriteDelay"]);
        new_configuration.m_shift_delay = stoi(cm["Tape"]["ShiftDelay"]);
        new_configuration.m_rewind_delay = stoi(cm["Tape"]["RewindDelay"]);
    }
    void RunTests()
    {
        {
            LOG_DURATION("Tests with small tape that fits into memory");
            tr.RunTest(TestsFit(), "Tests with small tape that fits into memory");
        }
        {
            LOG_DURATION("Tests with small tape that doesn't fit into memory");
            tr.RunTest(TestsNotFit(), "Tests with small tape that doesn't fit into memory");
        }
        {
            LOG_DURATION("Tests with big tape that fits into memory");
            tr.RunTest(TestsBigFit(), "Tests with big tape that fits into memory");
        }
        {
            LOG_DURATION("Tests with big tape that doesn't fit into memory");
            tr.RunTest(TestsBigNotFit(), "Tests with big tape that doesn't fit into memory");
        }
    }
};

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string input_filename = argv[1];
    std::string output_filename = argv[2];

    UnitTester ut(input_filename, output_filename);
    {
        LOG_DURATION("Total Test Time")
        ut.RunTests();
    }
    return 0;
}