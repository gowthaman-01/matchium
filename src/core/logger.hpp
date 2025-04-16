#pragma once

#include <string_view>

class Logger {
public:
    static void info(const std::string_view& context, const std::string_view& message);
    
    static void error(const std::string_view& context, const std::string_view& message);
};
