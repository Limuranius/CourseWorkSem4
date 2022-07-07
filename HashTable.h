#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

int bits_in_number(int num);

int get_mid_mask(int len, int shift_left);

template<typename T1, typename T2>
class HashTable {
public:

    HashTable(int (*obj_to_int)(const T1 &));

    ~HashTable();

    int double_hash(const T1 &obj, int try_number);

    void set(const T1 &key, const T2 &value, bool check_filling = true);

    T2 get(const T1 &key);

    bool has(const T1 &key);

    void remove(const T1 &key);

    void remove(const T1 &key, const T2 &value);

    void print_both_hashes(const T1 &key);

    void print();

    std::string to_string(std::string (*val1_to_str)(T1), std::string (*val2_to_str)(T2));

    int get_size();

    int get_count();

    int get_index_status(int i);

    std::vector<std::pair<T1, T2>> to_vector_status_1();

    std::vector<std::pair<T1, T2>> to_vector_status_all();

    void clear();

private:
    int min_size = 8;  // Минимально возможный размер таблицы. Не будет уменьшаться меньше этого значения
    T1 *keys;
    T2 *values;
    int *status;  // Массив статусов. 0 - пусто, 1 - занято, 2 - удалено
    int size;  // Размер массива. Всегда является степенью двойки
    int size_power;  // В какую степень нужно возвести 2, чтобы получить размер массива
    int curr_count;  // Текущее количество элементов в таблице
    int (*obj_to_int)(const T1 &);  // Функция, переводящая объект T1 в число для хеширования

    int primary_hash(int value);

    int secondary_hash(int value);

    int find_free_index(const T1 &key);

    void set_new_size(int new_size, int new_power);

    int get_index(const T1 &key);

    void check_filling();


};

template<typename T1, typename T2>
HashTable<T1, T2>::HashTable(int (*obj_to_int)(const T1 &)) {
    this->obj_to_int = obj_to_int;
    this->size = 8;
    this->size_power = 3;
    this->curr_count = 0;
    this->keys = new T1[this->size];
    this->values = new T2[this->size];
    this->status = new int[this->size];
    for (int i = 0; i < this->size; i++) this->status[i] = 0;  // Помечаем все ячейки пустыми
}

template<typename T1, typename T2>
int HashTable<T1, T2>::primary_hash(int value) {
    // Хеширование числа методом "середина квадрата"
    value = value % INT16_MAX;  // Чтобы при возведении в квадрат не было переполнения
    value = value * value;  // Возводим число в квадрат

    // Вычисляем маску для получения средних битов числа
    int value_len = bits_in_number(value);  // Высчитываем количество значимых битов в числе
    int mid_len = this->size_power;  // Количество битов, которые мы берём из середины
    int shift_left = value_len / 2 - mid_len / 2;  // На сколько битов от начала сдвинута середина
    int mid_mask = get_mid_mask(mid_len, shift_left);

    // Берём средние биты числа
    int res = value & mid_mask;
    res = res >> shift_left;  // Сдвигаем среднюю часть обратно к началу

    return res;
}

template<typename T1, typename T2>
int HashTable<T1, T2>::secondary_hash(int value) {
    // Хеширование методом умножения
    double A = 0.6180339887;
    double remain = fmod(value * A, 1);
    int result = this->size * remain;
    if (result % 2 == 0) {  // Делаем вторичный хеш нечётным, чтобы избежать зацикливания двойного хеширования
        if (result == 0)
            return result + 1;
        return result - 1;
    }
    return result;
}

template<typename T1, typename T2>
int HashTable<T1, T2>::double_hash(const T1 &obj, int try_number) {
    // Находит результат двойного хеширования объекта obj на попытке try_number
    int value = this->obj_to_int(obj);
    return (this->primary_hash(value) +
            try_number * this->secondary_hash(value)
           ) % this->size;
}

template<typename T1, typename T2>
int HashTable<T1, T2>::find_free_index(const T1 &key) {
    // Возвращает индекс свободной ячейки для ключа key
    int hash = this->double_hash(key, 0);
    int try_number = 1;
    while (this->get_index_status(hash) == 1) {  // Пока происходит коллизия
        hash = this->double_hash(key, try_number);
        try_number++;
    }
    return hash;
}

template<typename T1, typename T2>
int HashTable<T1, T2>::get_index(const T1 &key) {
    // Если ключ есть в таблице, то возвращает его индекс в массиве, иначе -1
    int hash = this->double_hash(key, 0);
    int try_number = 1;
    while (this->get_index_status(hash) != 0) {  // Пока не попали на полностью пустую ячейку
        if (this->keys[hash] == key &&
            this->get_index_status(hash) == 1)  // Если статус 2, то ячейка удалена и не должна быть найдена
            return hash;
        hash = this->double_hash(key, try_number);
        try_number++;
    }
    return -1;
}

template<typename T1, typename T2>
void HashTable<T1, T2>::set(const T1 &key, const T2 &value, bool check_filling) {
    // Ищем индекс подходящей ячейки
    int index = this->get_index(key);
    if (index == -1)  // Если ключа нет в таблице
        index = find_free_index(key);

    if (this->get_index_status(index) != 1)  // Если мы не заменяем, а добавляем элемент, то увеличиваем счётчик
        this->curr_count++;

    this->status[index] = 1;
    this->keys[index] = key;
    this->values[index] = value;


    if (check_filling) {  // Проверяем заполненность таблицы
        this->check_filling();
    }
}

template<typename T1, typename T2>
int HashTable<T1, T2>::get_index_status(int i) {
    return this->status[i];
}

template<typename T1, typename T2>
void HashTable<T1, T2>::set_new_size(int new_size, int new_power) {
    T1 *old_keys = this->keys;
    T2 *old_values = this->values;
    int *old_status = this->status;
    int old_max = this->size;

    // Создаём новые массивы таблицы
    this->keys = new T1[new_size];
    this->values = new T2[new_size];
    this->status = new int[new_size];
    for (int i = 0; i < new_size; i++) this->status[i] = 0;  // Обнуляем статусы в новой таблице
    this->size = new_size;
    this->size_power = new_power;
    this->curr_count = 0;

    // Переносим все данные с прошлой таблицы в новую
    for (int i = 0; i < old_max; i++) {
        if (old_status[i] == 1) {  // Добавляем только если ячейка существует
            this->set(old_keys[i], old_values[i], false);
        }
    }

    // Удаляем старые данные
    delete[] old_keys;
    delete[] old_values;
    delete[] old_status;
}

template<typename T1, typename T2>
bool HashTable<T1, T2>::has(const T1 &key) {
    return get_index(key) != -1;
}

template<typename T1, typename T2>
T2 HashTable<T1, T2>::get(const T1 &key) {
    int index = this->get_index(key);
    if (index == -1) {  // Если ключа нет
        throw std::runtime_error("Error: Key does not exist");
    }
    return this->values[index];
}

template<typename T1, typename T2>
void HashTable<T1, T2>::check_filling() {
    // Проверяет заполненность таблицы.
    // Если заполненность более 75%, то увеличивает таблицу.
    // Если заполненность менее 25%, то уменьшает таблицу.
    double fill_coefficient = double(this->curr_count) / double(this->size);
    if (fill_coefficient < 0.25 && this->size > this->min_size) {
        this->set_new_size(this->size / 2, this->size_power - 1);
    } else if (fill_coefficient > 0.75) {
        this->set_new_size(this->size * 2, this->size_power + 1);
    }
}

template<typename T1, typename T2>
void HashTable<T1, T2>::remove(const T1 &key) {
    int index = this->get_index(key);
    if (index == -1) {  // Если ключа нет
        throw std::runtime_error("Error: Key does not exist");
    }
    this->status[index] = 2;
    this->curr_count--;
    this->check_filling();
}

template<typename T1, typename T2>
void HashTable<T1, T2>::remove(const T1 &key, const T2 &value) {
    int index = this->get_index(key);
    if (index == -1) {  // Если ключа нет
        throw std::runtime_error("Error: Key does not exist");
    }
    if (this->values[index] == value) {
        this->status[index] = 2;
        this->curr_count--;
        this->check_filling();
    } else {
        throw std::runtime_error("Error: Key with value does not exist");
    }
}

template<typename T1, typename T2>
HashTable<T1, T2>::~HashTable() {
    delete[] this->keys;
    delete[] this->values;
    delete[] this->status;
}

template<typename T1, typename T2>
void HashTable<T1, T2>::print_both_hashes(const T1 &key) {
    std::cout << "Primary hash: " << this->primary_hash(this->obj_to_int(key)) << "\n";
    std::cout << "Secondary hash: " << this->secondary_hash(this->obj_to_int(key)) << "\n";
}

template<typename T1, typename T2>
int HashTable<T1, T2>::get_size() {
    return this->size;
}

template<typename T1, typename T2>
void HashTable<T1, T2>::print() {
    for (int i = 0; i < this->size; i++) {
        std::cout << i << " " << this->get_index_status(i) << " " << this->keys[i] << " : " << this->values[i]
                  << std::endl;
    }
}

template<typename T1, typename T2>
int HashTable<T1, T2>::get_count() {
    return this->curr_count;
}

/**
 * Переводит таблицу в вектор пар <Ключ, Значение>. Берёт только заполненные ячейки
 * @return Вектор пар <Ключ, Значение>
 */
template<typename T1, typename T2>
std::vector<std::pair<T1, T2>> HashTable<T1, T2>::to_vector_status_1() {
    std::vector<std::pair<T1, T2>> result = {};
    for (int i = 0; i < this->size; i++) {
        if (this->get_index_status(i) == 1) {
            std::pair<T1, T2> p;
            p.first = this->keys[i];
            p.second = this->values[i];
            result.push_back(p);
        }
    }
    return result;
}

template<typename T1, typename T2>
std::vector<std::pair<T1, T2>> HashTable<T1, T2>::to_vector_status_all() {
    std::vector<std::pair<T1, T2>> result = {};
    for (int i = 0; i < this->size; i++) {
        std::pair<T1, T2> p;
        p.first = this->keys[i];
        p.second = this->values[i];
        result.push_back(p);
    }
    return result;
}

template<typename T1, typename T2>
std::string HashTable<T1, T2>::to_string(std::string (*val1_to_str)(T1), std::string (*val2_to_str)(T2)) {
    std::string result = "";
    for (int i = 0; i < this->get_size(); i++) {
        int status = this->get_index_status(i);
        result += std::to_string(i) +
                  " " +
                  std::to_string(status);

        T1 key = this->keys[i];
        T2 value = this->values[i];

        // Выводим первичный и вторичные хеши для данного ключа
        if (status != 0) {  // Если ячейка не пустая, выводим значения
            result += " " +
                      val1_to_str(key) +
                      " : " +
                      val2_to_str(value) + " ";
            int prim_hash = this->double_hash(key, 0);
            result += "Первичный хеш: " + std::to_string(prim_hash) + ", ";
            if (prim_hash != i) {  // Если у данного ключа произошла коллизия, то выводим все вторичные хеши
                result += "Вторичные хеши: ";
                int try_count = 1;
                int sec_hash;
                do {
                    sec_hash = this->double_hash(key, try_count);
                    result += std::to_string(sec_hash) + ", ";
                    try_count++;
                } while (sec_hash != i);
            }
        }
        result += "\n";
    }
    return result;
}

template<typename T1, typename T2>
void HashTable<T1, T2>::clear() {
    for (int i = 0; i < this->get_size(); i++) {
        this->status[i] = 0;
    }
    this->set_new_size(8, 3);
}




