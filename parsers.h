#pragma once

#include <vector>
#include <string>
#include "Structures.h"

std::vector<std::string> split(const std::string& str, const std::string& delim);

std::vector<Planet> parse_planets_file(const std::string& file_path);

std::vector<Attribute> parse_attributes_file(const std::string& file_path);
