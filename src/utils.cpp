#include "utils.h"
#include <sstream>
#include <iomanip>

std::string limit_double(double num){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << num;
    return oss.str();
}

bool is_int(const std::string& str){
    size_t len = str.size();
    if (!len) return false;
    size_t i = 0;
    if (str[i] == '-') {
        i++;
        if (len == 1) return false;
    }
    for (; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}