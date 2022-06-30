#include "ReferenceAttributes.h"
#include <fstream>
#include "parsers.h"


/**
 * Конструктор справочника "Признаки планет"
 */
ReferenceAttributes::ReferenceAttributes() {
    this->DB = RBTree<climate_node_data>();
}

/**
 * Добавляет в справочник признак о планете. Не производит проверки на дубликаты
 * @param planet_name Название планеты
 * @param climate Тип климата
 * @param attr Признак планеты
 */
void ReferenceAttributes::add(const string &planet_name, const string &climate, const string &attr) {
    // Создаём структуры, работающие с КЧ деревом
    climate_node_data clim_data;
    clim_data.climate = climate;
    attribute_node_data attr_data;
    attr_data.attribute = attr;

    // Работаем с КЧ климатов
    if (!this->DB.has(clim_data)) {
        this->DB.add(clim_data);  // Если нет записи про данный климат, то добавляем
    }
    auto &attrs_tree = this->DB.find(clim_data)->val.attrs_tree;  // У данного климата рассматриваем дерево признаков

    // Работаем с КЧ признаков
    if (!attrs_tree.has(attr_data)) {
        attrs_tree.add(attr_data);  // Если нет записи про признак, то добавляем
    }
    auto &planets_list = attrs_tree.find(
            attr_data)->val.planets_list;  // У данного признака рассматривает список планет

    // Работаем со списком планет
    planets_list.insert(planet_name);
}

/**
 * Возвращает true, если в справочнике уже существует данная запись
 * @param planet_name Название планеты
 * @param climate Тип климата
 * @param attr Признак планеты
 * @return true, если запись существует, false, если не существует
 */
bool ReferenceAttributes::has(const string &planet_name, const string &climate, const string &attr) {
    // Создаём структуры, работающие с КЧ деревом
    climate_node_data clim_data;
    clim_data.climate = climate;
    attribute_node_data attr_data;
    attr_data.attribute = attr;

    if (!this->DB.has(clim_data))
        return false;
    auto attrs_tree = this->DB.find(clim_data)->val.attrs_tree;

    if (!attrs_tree.has(attr_data))
        return false;
    auto planets_list = attrs_tree.find(attr_data)->val.planets_list;

    return planets_list.has(planet_name);
}

/**
 * Удаляет из справочника данную запись. Не производит проверку на существование записи, подразумевает, что запись существует
 * @param planet_name Название планеты
 * @param climate Тип климата
 * @param attr Признак планеты
 */
void ReferenceAttributes::remove(const string &planet_name, const string &climate, const string &attr) {
    // Создаём структуры, работающие с КЧ деревом
    climate_node_data clim_data;
    clim_data.climate = climate;
    attribute_node_data attr_data;
    attr_data.attribute = attr;

    auto &attr_tree = this->DB.find(clim_data)->val.attrs_tree;  // Получаем дерево признаков для данного климата
    auto &planets_list = attr_tree.find(attr_data)->val.planets_list;  // Получаем список планет для данного признака

    // Удаляем снизу вверх. Сначала из списка планет, затем из дерева признаков, затем из дерева климатов
    // При этом проверяем, если структуры становятся пустыми, тогда их тоже можно удалить
    planets_list.remove(planet_name);
    if (planets_list.isEmpty()) {  // Если после удаления список планет стал пустым
        attr_tree.remove(attr_data);  // Удаляем из дерева признаков данный признак, т. к. теперь он ничего не содержит
    }
    if (attr_tree.isEmpty()) {  // Если после удаления планет и признаков дерево признаков для климата стало пустым
        this->DB.remove(clim_data);  // Удаляем из справочника климат, так как он теперь не содержит информации
    }
}

/**
 * Возвращает вектор признаков, содержащихся в справочнике
 * @return Вектор структур <Название, Климат, Признак>
 */
vector<Attribute> ReferenceAttributes::to_vector() {
    vector<Attribute> result = {};
    auto climates_vector = this->DB.to_vector();  // Получаем все климаты
    for (auto &clim_data: climates_vector) {
        auto attrs_vector = clim_data.attrs_tree.to_vector();  // У каждого климата получаем все признаки
        for (auto &attr_data: attrs_vector) {
            auto planets_list = attr_data.planets_list;  // У каждого признака получаем список планет
            for (auto &planet_name: planets_list.to_vector()) {  // Проходимся по каждой планете
                Attribute attr;  // Создаём запись из климата, признака и планеты
                attr.planet_name = planet_name;
                attr.attribute = attr_data.attribute;
                attr.climate = clim_data.climate;
                result.push_back(attr);
            }
        }
    }
    return result;
}

/**
 * Возвращает все признаки заданной планеты
 * @param planet_name Название планеты
 * @return Все признаки планеты
 */
vector<Attribute> ReferenceAttributes::get_all_planet_occurrences(const string &planet_name) {
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
void ReferenceAttributes::remove_all_planet_occurrences(const string &planet_name) {
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
void ReferenceAttributes::load_file(const string &file_path) {
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
void ReferenceAttributes::save_to_file(const string &file_path) {
    vector<Attribute> attrs = this->to_vector();
    ofstream out(file_path);
    string delimiter = "  #  ";
    for (Attribute& attr: attrs) {
        out << attr.planet_name << delimiter
            << attr.climate << delimiter
            << attr.attribute << "\n";
    }
    out.close();
}

List<string> ReferenceAttributes::find_planets(const string &climate, const string &attr) {
    // Создаём структуры, работающие с КЧ деревом
    climate_node_data clim_data;
    clim_data.climate = climate;
    attribute_node_data attr_data;
    attr_data.attribute = attr;

    auto &attrs_tree = this->DB.find(clim_data)->val.attrs_tree;  // У данного климата рассматриваем дерево признаков
    auto &planets_list = attrs_tree.find(
            attr_data)->val.planets_list;  // У данного признака рассматривает список планет
    return planets_list;
}

string ReferenceAttributes::to_string() {
    string result = "";
    auto climates_vector = this->DB.to_vector();  // Получаем все климаты
    for (auto &clim_data: climates_vector) {
        result += clim_data.climate + "\n";
        auto attrs_vector = clim_data.attrs_tree.to_vector();  // У каждого климата получаем все признаки
        for (auto &attr_data: attrs_vector) {
            result += "\t" + attr_data.attribute + "\n";
            auto planets_list = attr_data.planets_list;  // У каждого признака получаем список планет
            for (auto &planet_name: planets_list.to_vector()) {  // Проходимся по каждой планете
                result += "\t\t" + planet_name + "\n";
            }
        }
    }
    return result;
}

