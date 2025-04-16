#include "server.hpp"

#include "../core/constants.hpp"

int main() {
    HTTPServer server(Constants::port);
    server.start();
}
