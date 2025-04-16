#include "socket.hpp"

#include "error.hpp"
#include "logger.hpp"
#include "logger_macros.hpp"

int create_tcp_socket() {
    // Create a TCP socket (IPv4, stream-based)
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        Error::fatal("socket");
    }
    
    // To prevent "Address already in use" error on restart.
    int reuse = 1;
    int opt_status = setsockopt(
        fd,
        SOL_SOCKET,
        SO_REUSEADDR,
        &reuse,
        sizeof(reuse)
    );
    if (opt_status != 0) {
        Error::fatal("setsockopt", fd);
    }
    
    LOG_INFO("TCP socket created");
    
    return fd;
}

sockaddr_in create_server_address(int port) {
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    return server_addr;
}
