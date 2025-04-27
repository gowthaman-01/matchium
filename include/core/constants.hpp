#pragma once

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

namespace Constants {
    // Networking / System Config
    inline constexpr int default_backlog { 5 };
    inline constexpr int tcp_protocol { 0 };
    inline constexpr int default_port { 4221 };
    inline constexpr std::size_t buffer_size { 1024 };

    // HTTP Status Codes
    inline constexpr int ok_status_code { 200 };
    inline constexpr int not_found_status_code { 404 };

    // HTTP Status Messages
    inline const std::string OK_STATUS_MESSAGE { "OK" };
    inline const std::string NOT_FOUND_STATUS_MESSAGE { "Not Found" };

    // HTTP Formatting
    inline const std::string CRLF { "\r\n" };
    inline const std::string SPACE { " " };
    inline const std::string COLON_SPACE { ": " };

    // HTTP Version
    inline const std::string HTTP_VERSION { "HTTP/1.1" };

    // HTTP Header Fields
    inline const std::string CONTENT_LENGTH { "Content-Length" };

    // HTTP Methods
    enum class RequestMethod {
        GET,
        POST,
        PUT,
    };
    inline const std::string GET_METHOD { "GET" };

    // HTTP Paths
    inline const std::string SNAPSHOT_PATH { "/snapshot" };

    // HTTP Headers
    const std::unordered_map<std::string, std::string> default_headers = {
        {"Content-Type", "text/plain"},
        {"Connection", "close"},
        {"Server", "Matchium"}
    };

    // Logging constants
    inline constexpr int padding_width { 40 };

    enum class Role {
        Server,
        Client
    };

    // To string methods
    inline std::string to_string(Role role) {
        switch (role) {
            case Role::Server:
                return "server";
            case Role::Client:
                return "client";
        }
        throw std::invalid_argument("Invalid Role");
    }
    
    inline std::string to_string(RequestMethod request_method) {
        switch (request_method) {
            case RequestMethod::GET:
                return "GET";
            case RequestMethod::POST:
                return "POST";
            case RequestMethod::PUT:
                return "PUT";
        }
        throw std::invalid_argument("Invalid Method");
    }
}

