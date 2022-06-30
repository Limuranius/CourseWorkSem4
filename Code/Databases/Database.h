#pragma once

#include "ReferencePlanets.h"
#include "ReferenceAttributes.h"
#include <string>
#include <vector>

using namespace std;

struct PlanetFullInfo {
    string planet_name;
    double distance;
    int price;
    string climate;
    string attribute;
};

class Database {
public:
    void read_planets_file(const string &file_path);

    void read_attributes_file(const string &file_path);

    void save_planets_to_file(const string &file_path);

    void save_attributes_to_file(const string &file_path);

    void set_planet(const string &planet_name, double distance, int price);

    void add_attribute(const string &planet_name, const string &climate, const string &attribute);

    void remove_planet(const string &planet_name);

    void remove_attribute(const string &planet_name, const string &climate, const string &attribute);

    vector<Attribute> get_planet_attributes(const string &planet_name);

    bool has_planet(const string &planet_name);

    bool has_attribute(const string &planet_name, const string &climate, const string &attribute);

    vector<PlanetFullInfo> search(double distance, int price, const string &climate, const string &attribute);

    string planets_to_string();

    string attributes_to_string();

private:
    ReferencePlanets planets;
    ReferenceAttributes attributes;
};


