#pragma once

#include <string_view>

class Logger {
public:
    static void info(std::string_view context, std::string_view message);
    
    static void error(std::string_view context, std::string_view message);
};
