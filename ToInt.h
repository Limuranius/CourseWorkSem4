#pragma once

#include <string>

/**
 * Функции, переводящие различные структуры в число
 * Используется в хеш-таблицах при хешировании ключей
 */

int str_to_int(const std::string &str);

int int_to_int(const int &num);

