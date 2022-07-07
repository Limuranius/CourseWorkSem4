#pragma once

#include "Planets.h"
#include "Attributes.h"
#include <string>
#include <vector>

using namespace std;

class Database {
public:
    void read_planets_file(const string &file_path);

    void read_attributes_file(const string &file_path);

    void save_planets_to_file(const string &file_path);

    void save_attributes_to_file(const string &file_path);

    AddResult add_planet(const string &planet_name, double distance, int price);

    AddResult add_attribute(const string &planet_name, const string &climate, const string &attribute);

    RemoveResult remove_planet(const string &planet_name);  // ОКadsfasdfasdfsadf

    RemoveResult remove_attribute(const string &planet_name, const string &climate, const string &attribute);

    vector<Planet> get_all_planets();

    vector<Attribute> get_all_attributes();

    bool has_planet(const string &planet_name);


    // Задачи поиска:

    Planet get_planet(const string &planet_name);

    vector<Planet> get_planets_lower_distance(double distance);

    vector<Planet> get_planets_lower_price(int price);

    vector<Attribute> get_attributes_by_planet(const string &planet_name);

    vector<Attribute> get_attributes_by_climate(const string &climate);

    vector<Attribute> get_attributes_by_attribute(const string &attribute);

    vector<PlanetFullInfo> search(double distance, int price, const string &climate,
                                  const string &attribute);


    // Строковый вывод:

    string search_to_string(double distance, int price, const string &climate, const string &attribute);

    string planets_to_string_planet_table();

    string planets_to_string_distance_tree();

    string planets_to_string_price_tree();

    string attributes_to_string_planet_tree();

    string attributes_to_string_climate_tree();

    string attributes_to_string_attribute_tree();


private:
    Attributes attributes;
    Planets planets;
};


