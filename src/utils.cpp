#include "utils.h"
#include <sstream>
#include <iomanip>

std::string limit_double(double num){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << num;
    return oss.str();
}

bool is_int(const std::string& str){
    double a = std::stod(str);
    long long c = std::stoll(str);
    if((double)c == a) return true;
    else return false;
}