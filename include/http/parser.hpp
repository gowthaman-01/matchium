#pragma once

#include "request.hpp"

#include <string_view>

[[nodiscard]] Request parse_request(std::string_view message);
