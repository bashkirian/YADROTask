/**
 * @file configuration.h
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
/**
 * @brief Пространство имен для конфигурации
 */
namespace configuration
{
    /**
     * @brief Структура конфигурации
     */
    struct Configuration
    {
        int m_rewind_delay; // задержка перемотки
        int m_shift_delay; // задержка движения на одну позицию
        int m_read_delay; // задержка чтения
        int m_write_delay; // задержка записывания 
    };
}