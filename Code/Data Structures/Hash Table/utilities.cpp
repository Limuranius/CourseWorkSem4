#include <iostream>
#include "utilities.h"

int bits_in_number(int num) {
    // Возвращает, сколько значащих битов находятся в числе.
    // Например, 0 -> 0, 1 -> 1, 2 -> 2, 3 -> 2
    int res = 0;
    while (num != 0) {
        res++;
        num = num >> 1;
    }
    return res;
}

int get_mid_mask(int len, int shift_left) {
    int res = INT32_MAX;  // Заполняем переменную единицами
    res = res << len;
    res = ~res;
    res = res << shift_left;
    return res;
}

int str_to_int(const std::string& str) {
    int charSum = 0;
    for (unsigned char ch: str)  // unsigned, чтобы сумма всегда была положительной
        charSum += ch;
    return charSum;
}

int int_to_int(const int& num) {
    return num;
}
