#pragma once

namespace configuration
{
    struct Configuration
    {
        int m_rewind_delay; // задержка перемотки
        int m_shift_delay; // задержка движения на одну позицию
        int m_read_delay; // задержка чтения
        int m_write_delay; // задержка записывания 
    };
}