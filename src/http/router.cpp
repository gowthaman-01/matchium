#include "../../include/http/router.hpp"

#include "../../include/http/request.hpp"
#include "../../include/http/response.hpp"

void Router::register_handler(const std::string& method, const std::string& path,
                      std::function<Response(const Request&)> handler) {
    std::string key = method + path;
    routes_[key] = std::move(handler);
}

Response Router::route(const Request& request) {
    std::string key = request.method + request.path;
    auto it = routes_.find(key);
    if (it != routes_.end()) {
        auto handler = it->second;
        return handler(request);
    } else {
        return Response::NOT_FOUND();
    }
}
