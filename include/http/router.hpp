#pragma once

#include "request.hpp"
#include "response.hpp"

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

class Router {
private:
    std::unordered_map<std::string, std::function<Response(const Request&)>> routes_;
    
public:
    void register_handler(const std::string& method, const std::string& path,
                          std::function<Response(const Request&)> handler);
    
    Response route(const Request& request);
};
