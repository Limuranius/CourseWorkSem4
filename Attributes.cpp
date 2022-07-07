#include "Attributes.h"
#include <fstream>
#include "Parsers.h"


/**
 * Конструктор справочника "Признаки планет"
 */
Attributes::Attributes() {

}

/**
 * Добавляет в справочник признак о планете. Выводит ошибку, если такой признак уже существует
 * @param planet_name Название планеты
 * @param climate Тип климата
 * @param attr Признак планеты
 */
void Attributes::add(const string &planet_name, const string &climate, const string &attr) {
    if (this->has(planet_name, climate, attr)) {
        throw runtime_error("Error: Attribute already exist");
    }
    Attribute attribute = {planet_name, climate, attr};
    this->climate_tree.add(climate, attribute);
    this->planet_tree.add(planet_name, attribute);
    this->attribute_tree.add(attr, attribute);
}

/**
 * Возвращает true, если в справочнике уже существует данная запись
 * @param planet_name Название планеты
 * @param climate Тип климата
 * @param attr Признак планеты
 * @return true, если запись существует, false, если не существует
 */
bool Attributes::has(const string &planet_name, const string &climate, const string &attr) {
    return this->climate_tree.has(climate, {planet_name, climate, attr});
}

/**
 * Удаляет из справочника данную запись. Выводит ошибку, если такой записи не существует
 * @param planet_name Название планеты
 * @param climate Тип климата
 * @param attr Признак планеты
 */
void Attributes::remove(const string &planet_name, const string &climate, const string &attr) {
    if (!this->has(planet_name, climate, attr)) {
        throw runtime_error("Error: Can't remove attribute that not exist");
    }
    Attribute attribute = {planet_name, climate, attr};
    this->climate_tree.remove(climate, attribute);
    this->planet_tree.remove(planet_name, attribute);
    this->attribute_tree.remove(attr, attribute);
}

/**
 * Возвращает вектор признаков, содержащихся в справочнике
 * @return Вектор признаков
 */
vector<Attribute> Attributes::to_vector() {
    vector<Attribute> result = {};
    auto items = this->climate_tree.to_vector();
    for (auto item: items) {
        string climate = item.first;
        List<Attribute> chain = item.second;
        for (Attribute chain_item: chain.to_vector()) {
            Attribute attr;
            attr.planet_name = chain_item.planet_name;
            attr.attribute = chain_item.attribute;
            attr.climate = climate;
            result.push_back(attr);
        }
    }
    return result;
}

/**
 * Находит и возвращает все признаки с заданной планетой
 */
vector<Attribute> Attributes::get_attributes_by_planet(const string &planet_name) {
    if (this->planet_tree.has(planet_name)) {
        return this->planet_tree.find(planet_name)->chain.to_vector();
    } else {
        return {};
    }
}

vector<Attribute> Attributes::get_attributes_by_climate(const string &climate) {
    if (this->climate_tree.has(climate)) {
        return this->climate_tree.find(climate)->chain.to_vector();
    } else {
        return {};
    }
}

vector<Attribute> Attributes::get_attributes_by_attribute(const string &attribute) {
    if (this->attribute_tree.has(attribute)) {
        return this->attribute_tree.find(attribute)->chain.to_vector();
    } else {
        return {};
    }
}


/**
 * Удаляет все записи об определённой планете
 * @param planet_name Название планеты
 */
void Attributes::remove_all_planet_occurrences(const string &planet_name) {
    vector<Attribute> planet_occurrences = this->get_attributes_by_planet(planet_name);
    for (Attribute &attribute: planet_occurrences) {
        this->remove(
                attribute.planet_name,
                attribute.climate,
                attribute.attribute
        );  // Удаляем признак заданной планеты
    }
}

/**
 * Загружает признаки из файла
 * @param file_path Путь до файла
 */
void Attributes::load_file(const string &file_path) {
    vector<Attribute> parsed_attrs = parse_attributes_file(file_path);
    for (Attribute &attr: parsed_attrs) {
        this->add(
                attr.planet_name,
                attr.climate,
                attr.attribute
        );
    }
}

/**
 * Сохраняет справочник в файл
 * @param file_path Путь до файла
 */
void Attributes::save_to_file(const string &file_path) {
    vector<Attribute> attrs = this->to_vector();
    ofstream out(file_path);
    string delimiter = "  #  ";
    for (int i = 0; i < attrs.size(); i++) {
        Attribute attr = attrs[i];
        out << attr.planet_name << delimiter
            << attr.climate << delimiter
            << attr.attribute;
        if (i != attrs.size() - 1) {  // Чтобы в конце файла не выводить перевод строки
            out << "\n";
        }
    }
    out.close();
}

/**
 * Находит и возвращает названия всех планет, имеющих данный климат и отличительный признак
 */
vector<string> Attributes::find_planets(const string &climate, const string &attr) {
    vector<string> result = {};
    auto climate_chain = this->climate_tree.find(climate)->chain;
    for (auto &item: climate_chain.to_vector()) {
        if (item.attribute == attr) {
            result.push_back(item.planet_name);
        }
    }
    return result;
}

string Attributes::to_string_climate_tree() {
    return this->climate_tree.to_string(str_to_str, attribute_to_string);
}

string Attributes::to_string_attribute_tree() {
    return this->attribute_tree.to_string(str_to_str, attribute_to_string);
}

string Attributes::to_string_planet_tree() {
    return this->planet_tree.to_string(str_to_str, attribute_to_string);
}

void Attributes::clear() {
    this->climate_tree.clear();
    this->attribute_tree.clear();
    this->planet_tree.clear();
}

