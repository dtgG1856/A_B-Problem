#include "utils.h"
#include <sstream>
#include <iomanip>

std::string limit_double(double num) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << num;
    return oss.str();
}

bool is_int(const std::string& str) {
    size_t len = str.size();
    if (!len) return false;
    size_t i = 0;
    if (str[i] == '-') {
        i++;
        if (len == 1) return false;
    }
    int16_t numcnt = 0;
    for (; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
        numcnt++;
        if (numcnt >= 20) return false;
    }
    return true;
}

bool is_double(const std::string& str) {
    size_t len = str.size();
    if (!len) return false;
    size_t i = 0;
    if (str[i] == '-') {
        i++;
        if (len == 1) return false;
    }
    bool flag = false;
    int16_t numcnt = 0;
    for (; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            if (str[i] != '.' || flag) {
                return false;
            }
            flag = true;
        } else numcnt++;
        if(numcnt >= 17) return false;
    }
    return true;
}