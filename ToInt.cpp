#include "ToInt.h"

int str_to_int(const std::string &str) {
    int charSum = 0;
    for (unsigned char ch: str)  // unsigned, чтобы сумма всегда была положительной
        charSum += ch;
    return charSum;
}

int int_to_int(const int &num) {
    return num;
}
