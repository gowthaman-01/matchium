#pragma once

#include <string>
#include <unordered_map>
#include <utility>

/**
 * @brief Represents a HTTP Request with method, path, and headers.
 *
 * @var method  HTTP method string (e.g., "GET", "POST")
 * @var path Requested resource path (e.g., "/index.html")
 * @var headers Parsed headers as a map of key-value pairs
 */
struct Request {
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    
    Request(std::string method, std::string path, std::unordered_map<std::string, std::string> headers)
        : method(std::move(method)),
          path(std::move(path)),
          headers(std::move(headers)) {}
};
