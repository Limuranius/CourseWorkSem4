#pragma once

#include <vector>
#include "RBTree.h"
#include "List.h"
#include "Parsers.h"
#include "ToString.h"
#include "ToInt.h"

class Attributes {
public:
    Attributes();

    void load_file(const string &file_path);

    void save_to_file(const string &file_path);

    bool has(const string &planet_name, const string &climate, const string &attr);

    void add(const string &planet_name, const string &climate, const string &attr);

    void remove(const string &planet_name, const string &climate, const string &attr);

    void remove_all_planet_occurrences(const string &planet_name);

    void clear();

    vector<Attribute> get_attributes_by_planet(const string &planet_name);

    vector<Attribute> get_attributes_by_climate(const string &climate);

    vector<Attribute> get_attributes_by_attribute(const string &attribute);

    vector<Attribute> to_vector();

    vector<string> find_planets(const string &climate, const string &attr);

    string to_string_climate_tree();

    string to_string_attribute_tree();

    string to_string_planet_tree();

private:
    RBTree<string, Attribute> climate_tree;
    RBTree<string, Attribute> attribute_tree;
    RBTree<string, Attribute> planet_tree;
};

