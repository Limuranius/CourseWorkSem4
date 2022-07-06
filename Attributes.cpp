#include "Attributes.h"
#include <fstream>
#include "Parsers.h"


/**
 * Конструктор справочника "Признаки планет"
 */
Attributes::Attributes() {
    climate_tree = RBTree<string, Attribute>();
    attribute_tree = RBTree<string, Attribute>();
    planet_tree = RBTree<string, Attribute>();
}

/**
 * Добавляет в справочник признак о планете. Не производит проверки на дубликаты
 * @param planet_name Название планеты
 * @param climate Тип климата
 * @param attr Признак планеты
 */
void Attributes::add(const string &planet_name, const string &climate, const string &attr) {
    this->climate_tree.add(climate, {planet_name, attr});
    this->planet_tree.add(planet_name, {climate, attr});
    this->attribute_tree.add(attr, {planet_name, climate});
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
 * Удаляет из справочника данную запись. Не производит проверку на существование записи, подразумевает, что запись существует
 * @param planet_name Название планеты
 * @param climate Тип климата
 * @param attr Признак планеты
 */
void Attributes::remove(const string &planet_name, const string &climate, const string &attr) {
    Attribute attribute = {planet_name, climate, attr};
    this->climate_tree.remove(climate, attribute);
    this->planet_tree.remove(planet_name, attribute);
    this->attribute_tree.remove(attr, attribute);
}

/**
 * Возвращает вектор признаков, содержащихся в справочнике
 * @return Вектор структур <Название, Климат, Признак>
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
 * Возвращает все признаки заданной планеты
 * @param planet_name Название планеты
 * @return Все признаки планеты
 */
vector<Attribute> Attributes::get_all_planet_occurrences(const string &planet_name) {
    vector<Attribute> result = {};
    vector<Attribute> all_attributes = this->to_vector();
    for (Attribute &attribute: all_attributes) {  // Обходим все записи справочника
        if (attribute.planet_name == planet_name) {  // Если запись о заданной планете
            result.push_back(attribute);
        }
    }
    return result;
}


/**
 * Удаляет все записи об определённой планете
 * @param planet_name Название планеты
 */
void Attributes::remove_all_planet_occurrences(const string &planet_name) {
    vector<Attribute> planet_occurrences = this->get_all_planet_occurrences(planet_name);
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
    for (Attribute &attr: attrs) {
        out << attr.planet_name << delimiter
            << attr.climate << delimiter
            << attr.attribute << "\n";
    }
    out.close();
}

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

string Attributes::to_string() {
    return this->climate_tree.to_string(str_to_str, attribute_to_string);
}

