#pragma once

#include <string>
#include "Structures.h"

/**
 * Функции, переводящие различные структуры в строку
 * Используется при переводе хеш-таблиц и деревьев в строку
 */

std::string planet_to_string(Planet planet);

std::string attribute_to_string(Attribute attribute);

std::string str_to_str(std::string str);

std::string int_to_str(int num);

std::string double_to_str(double num);