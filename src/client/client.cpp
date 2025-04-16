#include "client.hpp"

#include "../core/error.hpp"
#include "../core/logger.hpp"
#include "../core/logger_macros.hpp"
#include "../core/socket.hpp"

#include <string>
#include <unistd.h>

Client::Client(int port) : port_(port), client_fd_(-1) {}

Client::~Client() {
    if (client_fd_ >= 0) {
        close(client_fd_);
        LOG_INFO("Client socket closed");
    }
}

void Client::start() {
    connect_to_server();
}

void Client::send_message(const std::string_view& message) {
    send(client_fd_, message.data(), message.length(), 0);
    LOG_INFO("Sent message to server: \"" + std::string(message) + "\"");
}

void Client::connect_to_server() {
    client_fd_ = create_tcp_socket();
    
    sockaddr_in server_addr = create_server_address(port_);
    sockaddr* addr_ptr = reinterpret_cast<sockaddr*>(&server_addr);
    
    // Connect to server.
    int connection_status = connect(client_fd_, addr_ptr, sizeof(server_addr));
    if (connection_status < 0) {
        Error::fatal("connect", client_fd_);
    }
    
    LOG_INFO("Connected to server on port " + std::to_string(port_));
}
