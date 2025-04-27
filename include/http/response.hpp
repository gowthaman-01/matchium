#pragma once

#include "../core/constants.hpp"

#include <string>
#include <unordered_map>
#include <utility>

struct Response {
    int status_code;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
    
    Response(int status_code, std::unordered_map<std::string, std::string> headers, std::string body)
        : status_code(status_code),
          headers(std::move(headers)),
          body(std::move(body)) {}
    
    static Response OK(const std::string& body) {
        return Response(Constants::ok_status_code, {{"Content-Type", "text/plain"}}, body);
    }
    
    static Response NOT_FOUND() {
        return Response(Constants::not_found_status_code,  {{"Content-Type", "text/plain"}}, "404 Not Found");
    }
};
