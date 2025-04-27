#pragma once

#include "request.hpp"
#include "response.hpp"

#include <string_view>

class Parser {
private:
    static std::string get_status_message(int status_code);
    
public:
    [[nodiscard]] static Request parse_request(std::string_view message);
    [[nodiscard]] static std::string serialise_response(Response& response);
};
