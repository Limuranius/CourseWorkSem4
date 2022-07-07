#include "Structures.h"

bool is_distance_correct(double distance) {
    return distance >= 0 && distance <= 13800000000;
}

bool is_price_correct(int price) {
    return price >= 0 && price <= 10000000;
}