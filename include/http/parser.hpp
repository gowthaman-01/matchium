#pragma once

#include "request.hpp"

#include <string_view>

Request parse_request(std::string_view message);
