#include "../../include/net/server_socket.hpp"

#include "../../include/core/constants.hpp"
#include "../../include/core/error.hpp"
#include "../../include/core/logger.hpp"
#include "../../include/core/logger_macros.hpp"
#include "../../include/core/utils.hpp"

#include <string>
#include <utility>

#include <netinet/in.h>
#include <sys/socket.h>

ServerSocket::ServerSocket(Socket&& socket, int port)
    : port_(port),
      socket_(std::move(socket)),
      address_(create_address(port)),
      is_listening_(false)
{
  bind_socket();
  listen_socket();
}

int ServerSocket::accept_client() {
    // Prepare client address
    sockaddr_in client_addr{};

    sockaddr* addr_ptr = reinterpret_cast<sockaddr*>(&client_addr);
    socklen_t client_len = sizeof(client_addr);

    LOG_INFO(Utility::format_identity(Constants::Role::Server, socket_.get_fd()) + " waiting for a client to connect...");

    // Accept a connection
    int client_fd = accept(socket_.get_fd(), addr_ptr, &client_len);
    if (client_fd < 0) {
        Error::fatal("accept", socket_.get_fd());
    }

    LOG_INFO(Utility::format_identity(Constants::Role::Server, socket_.get_fd())
             + " accepted new "
             + Utility::format_identity(Constants::Role::Client, client_fd));

    return client_fd;
}

sockaddr_in ServerSocket::create_address(int port) {
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    return server_addr;
}

void ServerSocket::bind_socket() {
    sockaddr* addr_ptr = reinterpret_cast<sockaddr*>(&address_);

    int bind_status = bind(socket_.get_fd(), addr_ptr, sizeof(address_));
    if (bind_status != 0) {
        Error::fatal("bind", socket_.get_fd());
    }
    
    LOG_INFO(Utility::format_identity(Constants::Role::Server, socket_.get_fd())
             + " successfully bound to port "
             + std::to_string(port_));
}

void ServerSocket::listen_socket() {
    int listen_status = listen(socket_.get_fd(), Constants::default_backlog);
    if (listen_status != 0) {
        Error::fatal("listen", socket_.get_fd());
    }
    is_listening_ = true;

    LOG_INFO(Utility::format_identity(Constants::Role::Server, socket_.get_fd())
             + " listening on port "
             + std::to_string(port_));
}
