#include "../../include/http/parser.hpp"

#include "../../include/core/constants.hpp"
#include "../../include/core/utils.hpp"
#include "../../include/http/request.hpp"
#include "../../include/http/response.hpp"

#include <string_view>
#include <iostream>
#include <vector>

Request Parser::parse_request(std::string_view message) {
    // Split the entire raw message into lines using CRLF as delimiter
    auto lines = Utility::split(message, Constants::CRLF);
    
    // Parse request line (first line: "METHOD PATH HTTP/VERSION")
    auto request_line_parts = Utility::split(lines[0], Constants::SPACE);       // "GET / HTTP/1.1" → ["GET", "/", "HTTP/1.1"]
    std::string method = request_line_parts[0];
    std::string path = request_line_parts[1];
    
    // Parse HTTP headers (lines[1:] are all header lines in "Key: Value" format)
    std::unordered_map<std::string, std::string> headers;
    for (size_t i = 1; i < lines.size(); ++i) {
        auto pair = Utility::split_once(lines[i], Constants::COLON_SPACE);      // "Host: localhost:4221" → {"Host": "localhost:4221"}
        headers[pair.first] = pair.second;
    }
    
    return Request(method, path, headers);
}

std::string Parser::serialise_response(Response& response) {
    std::string res = "";
    
    // Status Line
    res += Constants::HTTP_VERSION
    + " "
    + std::to_string(response.status_code)
    + " "
    + Parser::get_status_message(response.status_code)
    + Constants::CRLF;
    
    // Headers
    for (const auto& [key, value]: response.headers) {
        res += key
        + Constants::COLON_SPACE
        + value
        + Constants::CRLF;
    }
    
    // Content length
    res += Constants::CONTENT_LENGTH
    + Constants::COLON_SPACE
    + std::to_string(response.body.length())
    + Constants::CRLF;
    
    // Blank line
    res += Constants::CRLF;
    
    // Body
    res += response.body;
    
    return res;
}

std::string Parser::get_status_message(int status_code) {
    switch (status_code) {
        case 200:
            return Constants::OK_STATUS_MESSAGE;
        default:
            return Constants::NOT_FOUND_STATUS_MESSAGE;
    }
}
