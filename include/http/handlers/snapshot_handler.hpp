#pragma once

#include "../../core/constants.hpp"
#include "../response.hpp"
#include "../request.hpp"

inline Response snapshot_handler(const Request& req) {
    return Response(Constants::ok_status_code, Constants::default_headers, "Top 5 bids/asks (mock)");
}
