#include "Planets.h"


Planets::Planets() : table(str_to_int) {
}

/**
 * Добавляет планету в справочник. Выводит ошибку, если планета с таким названием уже есть
 */
void Planets::add(const string &planet_name, double distance, int price) {
    if (this->has(planet_name)) {
        throw runtime_error("Error: Can't add. Planet already exists");
    }
    Planet planet = {planet_name, distance, price};
    this->table.set(planet_name, planet);
    this->dist_tree.add(distance, planet);
    this->price_tree.add(price, planet);
}

/**
 * Удаляет планету из справочника. Выдаст ошибку, если такой планеты нет
 */
void Planets::remove(const string &planet_name) {
    if (!this->has(planet_name)) {
        throw runtime_error("Error: Can't remove planet that not exist");
    }
    Planet planet = this->table.get(planet_name);
    this->dist_tree.remove(planet.distance, planet);
    this->price_tree.remove(planet.price, planet);
    this->table.remove(planet_name);
}

/**
 * Удаляет планету из справочника. Выдаст ошибку, если такой планеты нет
 */
void Planets::remove(const string &planet_name, double distance, int price) {
    if (!this->has(planet_name)) {
        throw runtime_error("Error: Can't remove planet that not exist");
    }
    Planet planet = {planet_name, distance, price};
    this->dist_tree.remove(planet.distance, planet);
    this->price_tree.remove(planet.price, planet);
    this->table.remove(planet_name);
}

/**
 * Выдаёт планету по названию. Выдаст ошибку, если такой планеты нет
 */
Planet Planets::get(const string &planet_name) {
    if (!this->has(planet_name)) {
        throw runtime_error("Error: Planet not exist");
    }
    return this->table.get(planet_name);
}

/**
 * Возвращает true, если планета есть в справочнике
 */
bool Planets::has(const string &planet_name) {
    return this->table.has(planet_name);
}

/**
 * Возвращает все планеты из справочника
 */
vector<Planet> Planets::to_vector() {
    vector<Planet> result = {};
    for (auto &item: this->table.to_vector_status_1()) {
        Planet planet;
        planet.planet_name = item.first;
        planet.distance = item.second.distance;
        planet.price = item.second.price;
        result.push_back(planet);
    }
    return result;
}

void Planets::load_file(const string &file_path) {
    vector<Planet> parsed_planets = parse_planets_file(file_path);
    for (Planet &planet: parsed_planets) {
        this->add(planet.planet_name, planet.distance, planet.price);
    }
}

void Planets::save_to_file(const string &file_path) {
    vector<Planet> planets = this->to_vector();
    ofstream out(file_path);
    string deliminator = "  #  ";
    for (int i = 0; i < planets.size(); i++) {
        Planet planet = planets[i];
        out << planet.planet_name << deliminator
            << planet.distance << deliminator
            << planet.price;
        if (i != planets.size() - 1) {  // Чтобы в конце файла не выводить перевод строки
            out << "\n";
        }
    }
    out.close();
}

string Planets::to_string_HT() {
    return this->table.to_string(str_to_str, planet_to_string);
}

string Planets::to_string_dist_tree() {
    return this->dist_tree.to_string(double_to_str, planet_to_string);
}

string Planets::to_string_price_tree() {
    return this->price_tree.to_string(int_to_str, planet_to_string);
}

vector<Planet> Planets::find_lower_distance(double distance) {
    return this->dist_tree.get_sec_values_lower(distance);
}

vector<Planet> Planets::find_lower_price(int price) {
    return this->price_tree.get_sec_values_lower(price);
}

void Planets::clear() {
    this->table.clear();
    this->dist_tree.clear();
    this->price_tree.clear();
}
