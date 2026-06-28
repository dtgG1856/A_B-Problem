#include "routes.h"
#include "httplib.h"
#include <iostream>

int main() {
    httplib::Server svr;

    svr.set_pre_routing_handler([](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return httplib::Server::HandlerResponse::Unhandled;
    });

    register_routes(svr);

    std::cout << "C++ server running at http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}