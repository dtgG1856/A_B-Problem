#include <iostream>
#include <string>
#include "httplib.h"

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
            long long a = std::stoll(req.get_param_value("a"));
            long long b = std::stoll(req.get_param_value("b"));
            long long result = a + b;
            res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    // 减法
    svr.Get("/api/sub", [](const httplib::Request& req, httplib::Response& res) {
        try {
            long long a = std::stoll(req.get_param_value("a"));
            long long b = std::stoll(req.get_param_value("b"));
            long long result = a - b;
            res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    // 乘法
    svr.Get("/api/mul", [](const httplib::Request& req, httplib::Response& res) {
        try {
            long long a = std::stoll(req.get_param_value("a"));
            long long b = std::stoll(req.get_param_value("b"));
            long long result = a * b;
            res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    // 取模
    svr.Get("/api/mod", [](const httplib::Request& req, httplib::Response& res) {
        try {
            long long a = std::stoll(req.get_param_value("a"));
            long long b = std::stoll(req.get_param_value("b"));
            if (b == 0) {
                res.status = 400;
                res.set_content("{\"error\":\"除数不能为 0\"}", "application/json");
                return;
            }
            long long result = a % b;
            res.set_content("{\"result\":" + std::to_string(result) + "}", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid input\"}", "application/json");
        }
    });

    std::cout << "C++ server running at http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}