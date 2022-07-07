#pragma once

#include <string>
#include <fstream>
#include "HashTable.h"
#include "Parsers.h"
#include "RBTree.h"
#include "Structures.h"
#include "ToString.h"
#include "ToInt.h"

using namespace std;

class Planets {
public:
    Planets();

    void load_file(const string &file_path);

    void save_to_file(const string &file_path);

    bool has(const string &planet_name);

    Planet get(const string &planet_name);

    void add(const string &planet_name, double distance, int price);

    void remove(const string &planet_name);

    void remove(const string &planet_name, double distance, int price);

    void clear();

    string to_string_HT();

    string to_string_dist_tree();

    string to_string_price_tree();

    vector<Planet> to_vector();

    vector<Planet> find_lower_distance(double distance);

    vector<Planet> find_lower_price(int price);

private:
    HashTable<string, Planet> table;
    RBTree<double, Planet> dist_tree;
    RBTree<int, Planet> price_tree;
};
