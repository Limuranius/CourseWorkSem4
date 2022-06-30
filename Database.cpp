#include "Database.h"

void Database::read_planets_file(const string &file_path) {
    this->planets.load_file(file_path);
}

void Database::read_attributes_file(const string &file_path) {
    this->attributes.load_file(file_path);
}

void Database::save_planets_to_file(const string &file_path) {
    this->planets.save_to_file(file_path);
}

void Database::save_attributes_to_file(const string &file_path) {
    this->attributes.save_to_file(file_path);
}

void Database::set_planet(const string &planet_name, double distance, int price) {
    this->planets.set(planet_name, distance, price);
}

void Database::add_attribute(const string &planet_name, const string &climate, const string &attribute) {
    this->attributes.add(planet_name, climate, attribute);
}

void Database::remove_planet(const string &planet_name) {
    this->planets.remove(planet_name);
    this->attributes.remove_all_planet_occurrences(planet_name);
}

void Database::remove_attribute(const string &planet_name, const string &climate, const string &attribute) {
    this->attributes.remove(planet_name, climate, attribute);
}

vector<Attribute> Database::get_planet_attributes(const string &planet_name) {
    return this->attributes.get_all_planet_occurrences(planet_name);
}

bool Database::has_planet(const string &planet_name) {
    return this->planets.has(planet_name);
}

bool Database::has_attribute(const string &planet_name, const string &climate, const string &attribute) {
    return this->attributes.has(planet_name, climate, attribute);
}

vector<PlanetFullInfo> Database::search(double distance, int price, const string &climate, const string &attribute) {
    vector<PlanetFullInfo> result = {};

    // Находим список планет, подходящих по климату и признаку
    List<string> found_planets = this->attributes.find_planets(climate, attribute);

    // Проверяем, подходят ли эти планеты по расстоянию и цене
    for (string &planet_name: found_planets.to_vector()) {
        auto planet_info = this->planets.get(planet_name);
        if (planet_info.distance <= distance &&
            planet_info.price <= price) {  // Если планета подходит по всем параметрам
            PlanetFullInfo full_info;
            full_info.planet_name = planet_name;
            full_info.distance = planet_info.distance;
            full_info.price = planet_info.price;
            full_info.climate = climate;
            full_info.attribute = attribute;
            result.push_back(full_info);
        }
    }
    return result;
}

string Database::planets_to_string() {
    return this->planets.to_string();
}

string Database::attributes_to_string() {
    return this->attributes.to_string();
}

string Database::search_to_string(double distance, int price, const string &climate, const string &attribute) {
    vector<PlanetFullInfo> search_result = this->search(distance, price, climate, attribute);
    string result = "";
    for (PlanetFullInfo info: search_result) {
        result += info.planet_name + ":\n";
        result += "\tРасстояние: " + std::to_string(info.distance) + "\n";
        result += "\tЦена: " + std::to_string(info.price) + "\n";
        result += "\tКлимат: " + info.climate + "\n";
        result += "\tПризнак: " + info.attribute + "\n\n";
    }
    return result;
}
