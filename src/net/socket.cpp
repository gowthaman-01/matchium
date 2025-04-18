#include "socket.hpp"

#include "../core/constants.hpp"
#include "../core/error.hpp"
#include "../core/logger.hpp"
#include "../core/logger_macros.hpp"
#include "../core/utils.hpp"

#include <string>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Socket::Socket() : fd_(-1) {
    create_socket();
}

Socket::~Socket() {
    if (fd_ >= 0) {
        close(fd_);
        LOG_INFO(Utility::format_identity(Constants::Role::Server, fd_) + " closed");
    }
}

Socket::Socket(Socket&& other) noexcept : fd_(other.fd_) {
    other.fd_ = -1;
}

Socket& Socket::operator=(Socket&& other) noexcept {
    if (this != &other) {
        if (fd_ >= 0) {
            // Close existing fd_ before taking ownership of new one
            close(fd_);
            LOG_INFO(Utility::format_identity(Constants::Role::Server, fd_) + " closed");
        }
        fd_ = other.fd_;
        other.fd_ = -1;
    }
    return *this;
}

int Socket::get_fd() const {
    return fd_;
}

int Socket::release_fd() {
    int temp = fd_;
    fd_ = -1;
    return temp;
}

void Socket::create_socket() {
    // Create a TCP socket (IPv4, stream-based)
    fd_ = socket(AF_INET, SOCK_STREAM, Constants::tcp_protocol);
    if (fd_ < 0) {
        Error::fatal("socket");
    }
    
    // To prevent "Address already in use" error on restart.
    int reuse = 1;
    int opt_status = setsockopt(
        fd_,
        SOL_SOCKET,
        SO_REUSEADDR,
        &reuse,
        sizeof(reuse)
    );
    if (opt_status != 0) {
        Error::fatal("setsockopt", fd_);
    }
    
    LOG_INFO(Utility::format_identity(Constants::Role::Server, fd_) + " created");
}
