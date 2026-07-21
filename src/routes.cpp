#include "routes.h"
#include "utils.h"
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <stdexcept>

void register_routes(httplib::Server& svr) {
    // 加法
    svr.Get("/api/add", [](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string numA = req.get_param_value("a");
            std::string numB = req.get_param_value("b");
            if (!is_int(numA) || !is_int(numB)) {
                res.status = 400;
                res.set_content("{\"error\":\"您输入的数字不是整数\"}", "application/json");
                return;
            }
            int64_t a = std::stoll(numA);
            int64_t b = std::stoll(numB);
            bool overflow = false;
            if ((b > 0 && a > std::numeric_limits<int64_t>::max() - b) ||
                (b < 0 && a < std::numeric_limits<int64_t>::min() - b)) {
                overflow = true;  
            }  
            if (overflow) {
                res.status = 400;
                res.set_content("{\"error\":\"计算结果溢出\"}", "application/json");
            } else {
                int64_t result = a + b;
                res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
            }
        } catch (const std::out_of_range& e) {
            res.status = 400;
            res.set_content("{\"error\":\"您输入的数字过大\"}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"服务器状态错误\"}", "application/json");
        }
    });

    // 减法
    svr.Get("/api/sub", [](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string numA = req.get_param_value("a");
            std::string numB = req.get_param_value("b");
            if (!is_int(numA) || !is_int(numB)) {
                res.status = 400;
                res.set_content("{\"error\":\"您输入的数字不是整数\"}", "application/json");
                return;
            }
            int64_t a = std::stoll(numA);
            int64_t b = std::stoll(numB);
            bool overflow = false;
            if ((b < 0 && a > std::numeric_limits<int64_t>::max() + b) || 
                (b > 0 && a < std::numeric_limits<int64_t>::min() + b)) {
                    overflow = true;
            }
            if (overflow) {
                res.status = 400;
                res.set_content("{\"error\":\"计算结果溢出\"}", "application/json");
            } else {
                int64_t result = a - b;
                res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
            }
        } catch (const std::out_of_range& e) {
            res.status = 400;
            res.set_content("{\"error\":\"您输入的数字过大\"}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"服务器状态错误\"}", "application/json");
        }
    });

    // 乘法
    svr.Get("/api/mul", [](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string numA = req.get_param_value("a");
            std::string numB = req.get_param_value("b");
            if (!is_int(numA) || !is_int(numB)) {
                res.status = 400;
                res.set_content("{\"error\":\"您输入的数字不是整数\"}", "application/json");
                return;
            }
            int64_t a = std::stoll(numA);
            int64_t b = std::stoll(numB);
            bool overflow = false;
            if (a > b) std::swap(a, b);
            if ((a == std::numeric_limits<int64_t>::min() && b == -1)) {
                    overflow = true;
                }
            else if ((b < 0 && a > 0 && a > std::numeric_limits<int64_t>::min() / b) || 
                (b < 0 && a < 0 && a < std::numeric_limits<int64_t>::max() / b) ||
                (b > 0 && a > 0 && a > std::numeric_limits<int64_t>::max() / b) ||
                (b > 0 && a < 0 && a < std::numeric_limits<int64_t>::min() / b)) {
                    overflow = true;
            }
            if (overflow) {
                res.status = 400;
                res.set_content("{\"error\":\"计算结果溢出\"}", "application/json");
            } else {
                int64_t result = a * b;
                res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
            }
        } catch (const std::out_of_range& e) {
            res.status = 400;
            res.set_content("{\"error\":\"您输入的数字过大\"}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"服务器状态错误\"}", "application/json");
        }
    });

    // 取模
    /*svr.Get("/api/mod", [](const httplib::Request& req, httplib::Response& res) {
        try {
            double a = std::stod(req.get_param_value("a"));
            double b = std::stod(req.get_param_value("b"));
            if (b == 0) {
                res.status = 400;
                res.set_content("{\"error\":\"除数不能为 0\"}", "application/json");
                return;
            }
            double result = std::fmod(a, b);
            res.set_content("{\"result\":" + limit_double(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"服务器状态错误\"}", "application/json");
        }
    });

    // 异或
    svr.Get("/api/xor", [](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string str_a = req.get_param_value("a");
            std::string str_b = req.get_param_value("b");
            if(!is_int(str_a) || !is_int(str_b)) {
                res.status = 400;
                res.set_content("{\"error\":\"您输入的数字不是整数\"}", "application/json");
                return;
            }
            long long a = std::stoll(str_a);
            long long b = std::stoll(str_b);
            long long result = a ^ b;
            res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"服务器状态错误\"}", "application/json");
        }
    });

    // 最大公因数
    svr.Get("/api/gcd", [](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string str_a = req.get_param_value("a");
            std::string str_b = req.get_param_value("b");
            if(!is_int(str_a) || !is_int(str_b)) {
                res.status = 400;
                res.set_content("{\"error\":\"您输入的数字不是整数\"}", "application/json");
                return;
            }
            long long a = std::stoll(str_a);
            long long b = std::stoll(str_b);
            if (a == 0 && b == 0) {
                res.status = 400;
                res.set_content("{\"error\":\"您输入的数字不合法\"}", "application/json");
                return;
            }
            long long result = std::gcd(a,b);
            res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"服务器状态错误\"}", "application/json");
        }
    });

    //正弦函数
    svr.Get("/api/sin", [](const httplib::Request& req, httplib::Response& res) {
        try {
            double a = std::stod(req.get_param_value("a"));
            double result = std::sin(a);
            res.set_content("{\"result\":" + limit_double(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"服务器状态错误\"}", "application/json");
        }
    });

    //余弦函数
    svr.Get("/api/cos", [](const httplib::Request& req, httplib::Response& res) {
        try {
            double a = std::stod(req.get_param_value("a"));
            double result = std::cos(a);
            res.set_content("{\"result\":" + limit_double(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"服务器状态错误\"}", "application/json");
        }
    });

    //或运算
    svr.Get("/api/or",[](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string str_a = req.get_param_value("a");
            std::string str_b = req.get_param_value("b");
            if(!is_int(str_a) || !is_int(str_b)) {
                res.status = 400;
                res.set_content("{\"error\":\"您输入的数字不是整数\"}", "application/json");
                return;
            }
            long long a = std::stoll(str_a);
            long long b = std::stoll(str_b);
            long long result = a | b ;
            res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
        } catch(...) {
            res.status = 400;
            res.set_content("{\"error\":\"服务器状态错误\"}", "application/json");
        }
    });*/
}