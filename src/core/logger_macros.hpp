#pragma once

#include "utils.hpp"

#define LOG_CONTEXT "[" + std::string(get_filename(__FILE__)) + ":" + std::to_string(__LINE__) + " " + std::string(__func__) + "]"

#define LOG_INFO(msg) Logger::info(LOG_CONTEXT, msg)
#define LOG_ERROR(msg) Logger::error(LOG_CONTEXT, msg)
