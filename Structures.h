#pragma once

#include <string>

struct Planet {
    std::string planet_name;
    double distance;
    int price;

    bool operator==(const Planet &other) const {
        return planet_name == other.planet_name &&
               distance == other.distance &&
               price == other.price;
    }
};

struct Attribute {
    std::string planet_name;
    std::string climate;
    std::string attribute;

    bool operator==(const Attribute &other) const {
        return planet_name == other.planet_name &&
               climate == other.climate &&
               attribute == other.attribute;
    }
};

struct PlanetFullInfo {
    std::string planet_name;
    double distance;
    int price;
    std::string climate;
    std::string attribute;
};

bool is_distance_correct(double distance);

bool is_price_correct(int price);

enum class AddResult {
    SUCCESS, EXIST, NO_LINKED_PLANET
};

enum class RemoveResult {
    SUCCESS, NOT_FOUND
};