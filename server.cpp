#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "httplib.h"

std::string limit_double(double num){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << num;
    return oss.str();
}

bool is_int(std::string str){
    double a = std::stod(str);
    long long c = std::stoll(str);
    if((double)c == a) return true;
    else return false;
}

int main() {
    httplib::Server svr;

    // 允许跨域
    svr.set_pre_routing_handler([](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return httplib::Server::HandlerResponse::Unhandled;
    });

    // 加法
    svr.Get("/api/add", [](const httplib::Request& req, httplib::Response& res) {
        try {
            double a = std::stod(req.get_param_value("a"));
            double b = std::stod(req.get_param_value("b"));
            double result = a + b;
            res.set_content("{\"result\":" + limit_double(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    // 减法
    svr.Get("/api/sub", [](const httplib::Request& req, httplib::Response& res) {
        try {
            double a = std::stod(req.get_param_value("a"));
            double b = std::stod(req.get_param_value("b"));
            double result = a - b;
            res.set_content("{\"result\":" + limit_double(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    // 乘法
    svr.Get("/api/mul", [](const httplib::Request& req, httplib::Response& res) {
        try {
            double a = std::stod(req.get_param_value("a"));
            double b = std::stod(req.get_param_value("b"));
            double result = a * b;
            res.set_content("{\"result\":" + limit_double(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    // 取模
    svr.Get("/api/mod", [](const httplib::Request& req, httplib::Response& res) {
        try {
            double a = std::stod(req.get_param_value("a"));
            double b = std::stod(req.get_param_value("b"));
            if (b == 0) {
                res.status = 400;
                res.set_content("{\"error\":\"Invalid input\"}", "application/json");
                return;
            }
            double result = std::fmod(a, b);
            res.set_content("{\"result\":" + limit_double(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    // 异或
    svr.Get("/api/xor", [](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string str_a = req.get_param_value("a");
            std::string str_b = req.get_param_value("b");
            if(!is_int(str_a) || !is_int(str_b)){
                res.status = 400;
                res.set_content("{\"error\":\"Invalid input\"}", "application/json");
                return;
            }
            long long a = std::stoll(str_a);
            long long b = std::stoll(str_b);
            long long result = a ^ b;
            res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    // 最大公因数
    svr.Get("/api/gcd", [](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string str_a = req.get_param_value("a");
            std::string str_b = req.get_param_value("b");
            if(!is_int(str_a) || !is_int(str_b)){
                res.status = 400;
                res.set_content("{\"error\":\"Invalid input\"}", "application/json");
                return;
            }
            long long a = std::stoll(str_a);
            long long b = std::stoll(str_b);
            if (a == 0 && b == 0) {
                res.status = 400;
                res.set_content("{\"error\":\"Invalid input\"}", "application/json");
                return;
            }
            long long result = std::gcd(a,b);
            res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
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
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    std::cout << "C++ server running at http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}