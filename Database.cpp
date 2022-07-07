#include "Database.h"

void Database::read_planets_file(const string &file_path) {
    this->planets.clear();
    this->planets.load_file(file_path);
}

void Database::read_attributes_file(const string &file_path) {
    this->attributes.clear();
    this->attributes.load_file(file_path);
}

void Database::save_planets_to_file(const string &file_path) {
    this->planets.save_to_file(file_path);
}

void Database::save_attributes_to_file(const string &file_path) {
    this->attributes.save_to_file(file_path);
}

/**
 * Добавляет планету и возвращает статус выполнения
 * Возвращает:
 * SUCCESS - Успех. Планета добавлена
 * EXIST - Провал. В справочнике уже существует планета с таким названием
 */
AddResult Database::add_planet(const string &planet_name, double distance, int price) {
    if (this->planets.has(planet_name)) {
        return AddResult::EXIST;
    } else {
        this->planets.add(planet_name, distance, price);
        return AddResult::SUCCESS;
    }
}

/**
 * Добавляет признак и возвращает статус выполнения
 * Возвращает:
 * SUCCESS - Успех. Признак добавлен
 * EXIST - Провал. В справочнике уже существует такой же признак
 * NO_LINKED_PLANET - Провал. Попытка добавить признак для несуществующей планеты
 */
AddResult Database::add_attribute(const string &planet_name, const string &climate, const string &attribute) {
    if (this->attributes.has(planet_name, climate, attribute)) {
        return AddResult::EXIST;
    } else {
        if (this->planets.has(planet_name)) {
            this->attributes.add(planet_name, climate, attribute);
            return AddResult::SUCCESS;
        } else {
            return AddResult::NO_LINKED_PLANET;
        }
    }
}

/**
 * Удаляет планету и связанные с ней признаки и возвращает статус выполнения
 * Возвращает:
 * SUCCESS - Успех. Планета и связанные с ней признаки удалены
 * NOT_FOUND - Провал. Такой планеты нет в справочнике
 */
RemoveResult Database::remove_planet(const string &planet_name) {
    if (this->planets.has(planet_name)) {
        this->planets.remove(planet_name);
        this->attributes.remove_all_planet_occurrences(planet_name);
        return RemoveResult::SUCCESS;
    } else {
        return RemoveResult::NOT_FOUND;
    }
}

/**
 * Удаляет признак возвращает статус выполнения
 * Возвращает:
 * SUCCESS - Успех. Признак удалён
 * NOT_FOUND - Провал. Такого признака нет в справочнике
 */
RemoveResult Database::remove_attribute(const string &planet_name, const string &climate, const string &attribute) {
    if (this->attributes.has(planet_name, climate, attribute)) {
        this->attributes.remove(planet_name, climate, attribute);
        return RemoveResult::SUCCESS;
    } else {
        return RemoveResult::NOT_FOUND;
    }
}

vector<PlanetFullInfo> Database::search(double distance, int price, const string &climate, const string &attribute) {
    vector<PlanetFullInfo> result = {};

    // Находим список планет, подходящих по климату и признаку
    vector<string> found_planets = this->attributes.find_planets(climate, attribute);

    // Проверяем, подходят ли эти планеты по расстоянию и цене
    for (string &planet_name: found_planets) {
        Planet planet_info = this->planets.get(planet_name);
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

string Database::search_to_string(double distance, int price, const string &climate, const string &attribute) {
    vector<PlanetFullInfo> search_result = this->search(distance, price, climate, attribute);
    string result = "";
    for (PlanetFullInfo& info: search_result) {
        result += info.planet_name + ":\n";
        result += "\tРасстояние: " + std::to_string(info.distance) + "\n";
        result += "\tЦена: " + std::to_string(info.price) + "\n";
        result += "\tКлимат: " + info.climate + "\n";
        result += "\tПризнак: " + info.attribute + "\n\n";
    }
    return result;
}

vector<Planet> Database::get_all_planets() {
    return this->planets.to_vector();
}

vector<Attribute> Database::get_all_attributes() {
    return this->attributes.to_vector();
}

Planet Database::get_planet(const string &planet_name) {
    return this->planets.get(planet_name);
}

vector<Planet> Database::get_planets_lower_distance(double distance) {
    return this->planets.find_lower_distance(distance);
}

vector<Planet> Database::get_planets_lower_price(int price) {
    return this->planets.find_lower_price(price);
}

vector<Attribute> Database::get_attributes_by_planet(const string &planet_name) {
    return this->attributes.get_attributes_by_planet(planet_name);
}

vector<Attribute> Database::get_attributes_by_climate(const string &climate) {
    return this->attributes.get_attributes_by_climate(climate);
}

vector<Attribute> Database::get_attributes_by_attribute(const string &attribute) {
    return this->attributes.get_attributes_by_attribute(attribute);
}

string Database::planets_to_string_planet_table() {
    return this->planets.to_string_HT();
}

string Database::planets_to_string_distance_tree() {
    return this->planets.to_string_dist_tree();
}

string Database::planets_to_string_price_tree() {
    return this->planets.to_string_price_tree();
}

string Database::attributes_to_string_planet_tree() {
    return this->attributes.to_string_planet_tree();
}

string Database::attributes_to_string_climate_tree() {
    return this->attributes.to_string_climate_tree();
}

string Database::attributes_to_string_attribute_tree() {
    return this->attributes.to_string_attribute_tree();
}

bool Database::has_planet(const string &planet_name) {
    return this->planets.has(planet_name);
}
