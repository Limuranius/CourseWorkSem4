#include "ToString.h"

std::string planet_to_string(Planet planet) {
    return "(" + planet.planet_name + ", " +
           std::to_string(planet.distance) + ", " +
           std::to_string(planet.price) + ")";

}

std::string attribute_to_string(Attribute attribute) {
    return "(" + attribute.planet_name + ", " +
           attribute.climate + ", " +
           attribute.attribute + ")";
}

std::string str_to_str(std::string str) {
    return str;
}

std::string int_to_str(int num) {
    return std::to_string(num);
}

std::string double_to_str(double num) {
    return std::to_string(num);
}
