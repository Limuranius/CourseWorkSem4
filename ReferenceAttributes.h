#pragma once

#include "RBTree.h"
#include "List.h"
#include "parsers.h"
#include <vector>

// Иерархия структуры справочника: Климат(КЧ) -> Признак(КЧ) -> Название планеты(Список)

struct attribute_node_data {
    string attribute;
    List<string> planets_list;

    bool operator<(const attribute_node_data &other) const {  // Оператор нужен для добавления структуры в КЧ-дерево
        return this->attribute < other.attribute;
    }

    bool operator>(const attribute_node_data &other) const {  // Оператор нужен для добавления структуры в КЧ-дерево
        return this->attribute > other.attribute;
    }

    bool operator!=(const attribute_node_data &other) const {  // Оператор нужен для добавления структуры в КЧ-дерево
        return this->attribute != other.attribute;
    }
};

struct climate_node_data {
    string climate;
    RBTree<attribute_node_data> attrs_tree;

    bool operator<(const climate_node_data &other) const {  // Оператор нужен для добавления структуры в КЧ-дерево
        return this->climate < other.climate;
    }

    bool operator>(const climate_node_data &other) const {  // Оператор нужен для добавления структуры в КЧ-дерево
        return this->climate > other.climate;
    }

    bool operator!=(const climate_node_data &other) const {  // Оператор нужен для добавления структуры в КЧ-дерево
        return this->climate != other.climate;
    }
};

class ReferenceAttributes {
public:
    ReferenceAttributes();

    void load_file(const string &file_path);

    void save_to_file(const string &file_path);

    bool has(const string &planet_name, const string &climate, const string &attr);

    void add(const string &planet_name, const string &climate, const string &attr);

    void remove(const string &planet_name, const string &climate, const string &attr);

    void remove_all_planet_occurrences(const string &planet_name);

    vector<Attribute> get_all_planet_occurrences(const string &planet_name);

    vector<Attribute> to_vector();

    List<string> find_planets(const string &climate, const string &attr);

    string to_string();

    RBTree<climate_node_data> DB;
private:

};

