#include "logger.hpp"

#include <iostream>
#include <string_view>

void Logger::info(std::string_view context, std::string_view message) {
    std::cout << "[INFO] " << context << " " << message << '\n';
}

void Logger::error(std::string_view context, std::string_view message) {
    std::cerr << "[ERROR] " << context << " " << message << '\n';
}
