#pragma once

#include <vector>
#include <string>

struct Planet {
    std::string planet_name;
    double distance;
    int price;
};

struct Attribute {
    std::string planet_name;
    std::string climate;
    std::string attribute;
};

std::vector<std::string> split(const std::string& str, const std::string& delim);

std::vector<Planet> parse_planets_file(const std::string& file_path);

std::vector<Attribute> parse_attributes_file(const std::string& file_path);
