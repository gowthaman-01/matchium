#pragma once

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <string_view>

namespace Constants {
    inline constexpr int port { 4221 };
    inline constexpr int default_backlog { 5 };
    inline constexpr std::size_t buffer_size { 1024 };
    inline constexpr int tcp_protocol { 0 };
    inline constexpr int padding_width { 40 };
    inline constexpr std::string_view CRLF { "\r\n"};
    inline constexpr std::string_view SPACE { " " };
    inline constexpr std::string_view COLON_SPACE { ": " };

    enum class Role {
        Server,
        Client
    };

    /**
     * DESIGN NOTE:
     * We return std::string here (instead of std::string_view) because the result is
     * immediately used in string concatenation (e.g., "[" + to_string(role) + "]").
     */
    inline std::string to_string(Role role) {
        switch (role) {
            case Role::Server:
                return "server";
            case Role::Client:
                return "client";
        }
        throw std::invalid_argument("Invalid Role");
    }
    
    enum class RequestMethod {
        GET,
        POST,
        PUT,
    };

    // Same reason as above: used in string concatenation contexts.
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

