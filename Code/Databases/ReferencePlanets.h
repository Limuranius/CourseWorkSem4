#pragma once

#include "hash_table.h"
#include <string>
#include "parsers.h"
#include <fstream>

using namespace std;

struct HT_planet_value {  // Значения в хеш-таблице
    double distance;
    int price;

    bool operator==(const HT_planet_value &other) const {
        return (this->distance == other.distance) && (this->price == other.price);
    }
};

class ReferencePlanets {
public:
    ReferencePlanets();

    void load_file(const string &file_path);

    void save_to_file(const string &file_path);

    bool has(const string &planet_name);

    HT_planet_value get(const string &planet_name);

    void set(const string &planet_name, double distance, int price);

    void remove(const string &planet_name);

    void remove(const string &planet_name, double distance, int price);

    vector<Planet> to_vector();

    string to_string();

private:
    hash_table<string, HT_planet_value> table;
};
