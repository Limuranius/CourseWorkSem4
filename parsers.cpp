#include "parsers.h"
#include "fstream"
#include <iostream>

using namespace std;

vector<string> split(const string &str, const string &delim) {
    // Разбивает строку по разделителю delim
    vector<string> result = {};
    unsigned int start = 0;
    unsigned int end = str.find(delim);
    while (end != -1) {
        result.push_back(
                str.substr(start, end - start)
        );
        start = end + delim.size();
        end = str.find(delim, start);
    }
    result.push_back(str.substr(start, end - start));
    return result;
}


vector<Planet> parse_planets_file(const string &file_path) {
    string delimiter = "  #  ";  // Разделитель, по которому разделяем файл
    vector<Planet> result = {};
    ifstream inp(file_path);
    if (!inp) {  // Проверяем существование файла
        throw runtime_error("Error: File not exist");
    }

    string line;
    vector<string> split_line;
    while (getline(inp, line)) {  // Построчно читаем файл
        split_line = split(line, delimiter);
        Planet planet;
        planet.planet_name = split_line[0];
        planet.distance = stod(split_line[1]);
        planet.price = stoi(split_line[2]);
        result.push_back(planet);
    }
    inp.close();
    return result;
}

vector<Attribute> parse_attributes_file(const string &file_path) {
    string delimiter = "  #  ";  // Разделитель, по которому разделяем файл
    vector<Attribute> result = {};
    ifstream inp(file_path);
    if (!inp) {  // Проверяем существование файла
        throw runtime_error("Error: File not exist");
    }

    string line;
    vector<string> split_line;
    while (getline(inp, line)) {  // Построчно читаем файл
        split_line = split(line, delimiter);
        Attribute attr;
        attr.planet_name = split_line[0];
        attr.climate = split_line[1];
        attr.attribute = split_line[2];
        result.push_back(attr);
    }
    inp.close();
    return result;
}