#include "Planets.h"


Planets::Planets() : table(str_to_int) {
}

void Planets::set(const string &planet_name, double distance, int price) {
    Planet value = {planet_name, distance, price};
    this->table.set(planet_name, value);
}

void Planets::remove(const string &planet_name) {
    this->table.remove(planet_name);
}

void Planets::remove(const string &planet_name, double distance, int price) {
    Planet value = {planet_name, distance, price};
    this->table.remove(planet_name, value);
}

Planet Planets::get(const string &planet_name) {
    return this->table.get(planet_name);
}

bool Planets::has(const string &planet_name) {
    return this->table.has(planet_name);
}

vector<Planet> Planets::to_vector_occupied_cells() {
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
        this->set(planet.planet_name, planet.distance, planet.price);
    }
}

void Planets::save_to_file(const string &file_path) {
    vector<Planet> planets = this->to_vector_occupied_cells();
    ofstream out(file_path);
    string deliminator = "  #  ";
    for (Planet &planet: planets) {
        out << planet.planet_name << deliminator
            << planet.distance << deliminator
            << planet.price << "\n";
    }
    out.close();
}

string Planets::to_string_HT() {
    return this->table.to_string(str_to_str, planet_to_string);
}
