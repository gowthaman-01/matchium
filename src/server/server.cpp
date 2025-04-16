#include "server.hpp"

#include "../core/error.hpp"
#include "../core/logger.hpp"
#include "../core/logger_macros.hpp"
#include "../core/socket.hpp"

#include <unistd.h>

HTTPServer::HTTPServer(int port) : port_(port), server_fd_(-1) {}

HTTPServer::~HTTPServer() {
    if (server_fd_ >= 0) {
        close(server_fd_);
        LOG_INFO("Server socket closed");
    }
}

void HTTPServer::start() {
    setup_server();
    int client_fd = wait_for_client();
    handle_client(client_fd);
}

void HTTPServer::setup_server() {
    server_fd_ = create_tcp_socket();
    
    sockaddr_in server_addr = create_server_address(port_);
    sockaddr* addr_ptr = reinterpret_cast<sockaddr*>(&server_addr);
    
    //Associate the file descriptor with server address.
    int bind_status = bind(server_fd_, addr_ptr, sizeof(server_addr));
    if (bind_status != 0) {
        Error::fatal("bind", server_fd_);
    }
    
    // Listen to incoming connections.
    constexpr int backlog = 5; // Max number of queued connections.
    int listen_status = listen(server_fd_, backlog);
    if (listen_status != 0) {
        Error::fatal("listen", server_fd_);
    }
    
    LOG_INFO("Listening on port " + std::to_string(port_));
}

int HTTPServer::wait_for_client() {
    // Prepare client address
    sockaddr_in client_addr{};
    
    sockaddr* addr_ptr = reinterpret_cast<sockaddr*>(&client_addr);
    socklen_t client_len = sizeof(client_addr);
    
    LOG_INFO("Waiting for a client to connect...");
    
    // Accept a connection
    int client_fd = accept(server_fd_, addr_ptr, &client_len);
    if (client_fd < 0) {
        Error::fatal("accept", server_fd_);
    }
    
    LOG_INFO("Accepted new client connection");
    
    return client_fd;
}

void HTTPServer::handle_client(int client_fd) {
    char buffer[1024] = {0};
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_received > 0) {
        LOG_INFO("Received message from client: \"" + std::string(buffer) + "\"");
    } else {
        LOG_ERROR("Failed to receive data or client disconnected.");
    }
    
    close(client_fd);
    LOG_INFO("Client socket closed"); 
}
