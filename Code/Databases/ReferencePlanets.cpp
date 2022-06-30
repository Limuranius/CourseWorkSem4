#include "ReferencePlanets.h"

ReferencePlanets::ReferencePlanets() : table(str_to_int) {
}

void ReferencePlanets::set(const string &planet_name, double distance, int price) {
    HT_planet_value value = {distance, price};
    this->table.set(planet_name, value);
}

void ReferencePlanets::remove(const string &planet_name) {
    this->table.remove(planet_name);
}

void ReferencePlanets::remove(const string &planet_name, double distance, int price) {
    HT_planet_value value = {distance, price};
    this->table.remove(planet_name, value);
}

HT_planet_value ReferencePlanets::get(const string &planet_name) {
    return this->table.get(planet_name);
}

bool ReferencePlanets::has(const string &planet_name) {
    return this->table.has(planet_name);
}

vector<Planet> ReferencePlanets::to_vector() {
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

void ReferencePlanets::load_file(const string &file_path) {
    vector<Planet> parsed_planets = parse_planets_file(file_path);
    for (Planet &planet: parsed_planets) {
        this->set(planet.planet_name, planet.distance, planet.price);
    }
}

void ReferencePlanets::save_to_file(const string &file_path) {
    vector<Planet> planets = this->to_vector();
    ofstream out(file_path);
    string deliminator = "  #  ";
    for (Planet &planet: planets) {
        out << planet.planet_name << deliminator
            << planet.distance << deliminator
            << planet.price << "\n";
    }
    out.close();
}

string ReferencePlanets::to_string() {
    string result = "";
    auto items = this->table.to_vector_status_all();
    for (int i = 0; i < items.size(); i++) {
        auto item = items[i];
        int status = this->table.get_index_status(i);
        string planet_name = item.first;
        double distance = item.second.distance;
        int price = item.second.price;
        result += std::to_string(i) + " ";
        result += std::to_string(status) + " ";
        result += planet_name + " : ";
        result += std::to_string(distance) + ", ";
        result += std::to_string(price) + "\n";
    }
    return result;
}
