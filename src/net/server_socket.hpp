#pragma once

#include "socket.hpp"

#include "../core/constants.hpp"

#include <netinet/in.h>

/**
 * @brief A high-level wrapper around a TCP socket for server-side usage.
 *
 * This class manages the setup of a server socket, including:
 * - Creating a socket using the RAII-enabled `Socket` class
 * - Configuring the address (port, interface)
 * - Binding the socket to the specified address
 * - Preparing the socket to listen for incoming connections
 *
 * Future extensions may include:
 * - Support for multiple client connections
 * - Integration with `select()`, `poll()`, or `epoll()`
 */
class ServerSocket {
public:
    explicit ServerSocket(Socket&& socket, int port = Constants::port);
    
    [[nodiscard]] int accept_client();
    
private:
    const int port_;
    Socket socket_;
    
    sockaddr_in address_;
    // std::vector<int> client_fds_; // For multiclient support
    
    bool is_listening_;

    static sockaddr_in create_address(int port);
    void bind_socket();
    void listen_socket();
};
