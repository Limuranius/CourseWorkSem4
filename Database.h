#pragma once

#include "Planets.h"
#include "Attributes.h"
#include <string>
#include <vector>

using namespace std;

class Database {
public:
    void read_planets_file(const string &file_path);  // ОК

    void read_attributes_file(const string &file_path);  // ОК

    void save_planets_to_file(const string &file_path);  // ОК

    void save_attributes_to_file(const string &file_path);  // ОК

    void set_planet(const string &planet_name, double distance, int price);  // ОК

    void add_attribute(const string &planet_name, const string &climate, const string &attribute);  // ОК

    void remove_planet(const string &planet_name);  // ОК

    void remove_attribute(const string &planet_name, const string &climate, const string &attribute);  // ОК

    vector<Attribute> get_planet_attributes(const string &planet_name);  // ОК

    bool has_planet(const string &planet_name);  // ОК

    bool has_attribute(const string &planet_name, const string &climate, const string &attribute);  // ОК

    vector<PlanetFullInfo> search(double distance, int price, const string &climate, const string &attribute);  // Адаптировать под дерево цепочек

    string planets_to_string();  // ОК

    string attributes_to_string();  // ОК

    string search_to_string(double distance, int price, const string &climate, const string &attribute);  // ОК

private:
    Attributes attributes;
    Planets planets;
};


