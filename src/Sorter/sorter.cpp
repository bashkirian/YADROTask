#include "sorter.h"

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

void TapeSorter::tapesort(string input_filename, string output_filename, configuration::Configuration new_conf)
{
    TapeFile m_input_tape(input_filename, new_conf);  
    TapeFile m_output_tape(output_filename, new_conf);
    // Шаг 1: Разделить выходную ленту на ленты, помещающиеся в памяти
    vector<string> sub_tape_filenames;
    vector<unique_ptr<TapeFile>> sub_tapes = break_tape(m_input_tape, sub_tape_filenames);

    // Шаг 2: Слить суб-ленты, пока вся лента не будет отсортирована (сортировка слиянием с помощью кучи)
    merge_tapes(m_output_tape, sub_tapes);
}

vector<unique_ptr<TapeFile>> TapeSorter::break_tape(TapeFile& m_input_tape, vector<string>& sub_tape_filenames)
{
    vector<unique_ptr<TapeFile>> sub_tapes;
    m_input_tape.rewind();
    do 
    {
        // создать суб-ленту и написать отсортированный кусок входной ленты в него
        string sub_tape_filename = create_temporary_file();
        sub_tape_filenames.emplace_back(sub_tape_filename);
        TapeFile sub_tape(sub_tape_filename, m_input_tape.getConfiguration());
        vector<int> chunk;
        chunk.reserve(m_memory_limit);
        do
        {
            int value = m_input_tape.read(); // прочитать значение на ленте
            m_input_tape.shift(1); // подвинуть головку на 1 позицию
            chunk.emplace_back(value); // запушить число в чанк
        } while ((!m_input_tape.isended() && chunk.size() < m_memory_limit));
        sort(chunk.begin(), chunk.end()); // сортируем чанк
        sub_tape.rewind();
        for (int value : chunk)
        {
            sub_tape.write(value);
        }
        sub_tapes.emplace_back(make_unique<TapeFile>(sub_tape)); // пушим временную ленту в массив временных лент
    } while (!m_input_tape.isended());
    return sub_tapes;
}

void TapeSorter::merge_tapes(TapeFile& m_output_tape, vector<unique_ptr<TapeFile>>& sub_tapes)
{
    typedef pair<int, pair<int, int>> ppi; 
    priority_queue<ppi, vector<ppi>, greater<ppi>> pq;
    for (size_t i = 0; i < sub_tapes.size(); ++i)
    {
        sub_tapes[i]->rewind();
        pq.push({sub_tapes[i]->read(), {i, 0}}); // сделать так, чтобы пушились первые элементы лент
    }

    m_output_tape.rewind();
    while (pq.empty() == false)
    {
        ppi curr = pq.top();
        pq.pop();

        // i ==> Номер ленты
        // j ==> Индекс числа в ленте
        int i = curr.second.first;
        int j = curr.second.second;

        m_output_tape.write(curr.first);
        sub_tapes[i]->shift(1);
        // Если есть следующий элемент в ленте, из которой взяли текущий элемент
        if (!sub_tapes[i]->isended()) {
            pq.push({sub_tapes[i]->read(), {i, j + 1}});
        }
    }
}

// создание временной ленты в папке tmp
string TapeSorter::create_temporary_file()
{
    char buffer[256];
    sprintf(buffer, "tmp/tempfile_%d.txt", m_temporary_file_counter++);
    return string(buffer);
}
