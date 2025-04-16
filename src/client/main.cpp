#include "client.hpp"

#include "../core/constants.hpp"

int main() {
    Client client(Constants::port);
    client.start();
    client.send_message("Hello!");
}
