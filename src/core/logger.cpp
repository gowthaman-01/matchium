#include "logger.hpp"

#include <iostream>

void Logger::info(const std::string_view& context, const std::string_view &message) {
    std::cout << "[INFO] " << context << " " << message << '\n';
}

void Logger::error(const std::string_view& context, const std::string_view &message) {
    std::cerr << "[ERROR] " << context << " " << message << '\n';
}
