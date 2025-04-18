#include "parser.hpp"

#include "../core/constants.hpp"
#include "../core/utils.hpp"
#include "request.hpp"

#include <string_view>
#include <iostream>
#include <vector>

Request parse_request(std::string_view message) {
    // Split the entire raw message into lines using CRLF as delimiter
    auto lines = split(message, Constants::CRLF);
    
    // Parse request line (first line: "METHOD PATH HTTP/VERSION")
    auto request_line_parts = split(lines[0], Constants::SPACE);   // "GET / HTTP/1.1" → ["GET", "/", "HTTP/1.1"]
    std::string method = request_line_parts[0];
    std::string path = request_line_parts[1];
    
    // Parse HTTP headers (lines[1:] are all header lines in "Key: Value" format)
    std::unordered_map<std::string, std::string> headers;
    for (size_t i = 1; i < lines.size(); ++i) {
        auto pair = split_once(lines[i], Constants::COLON_SPACE);      // "Host: localhost:4221" → {"Host": "localhost:4221"}
        headers[pair.first] = pair.second;
    }
    
    return Request(method, path, headers);
}
