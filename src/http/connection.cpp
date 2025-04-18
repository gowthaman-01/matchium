#include "connection.hpp"

#include "../core/constants.hpp"
#include "../core/error.hpp"
#include "../core/logger.hpp"
#include "../core/logger_macros.hpp"
#include "../core/utils.hpp"

#include <string>

#include <sys/socket.h>
#include <unistd.h>

Connection::Connection(int client_fd) : client_fd_(client_fd) {}

Connection::~Connection() {
    if (client_fd_ >= 0) {
        close(client_fd_);
        LOG_INFO(format_identity(Constants::Role::Client, client_fd_) + " closed");
    }
}

Connection::Connection(Connection&& other) noexcept : client_fd_(other.client_fd_){
    other.client_fd_ = -1;
}

Connection& Connection::operator=(Connection &&other) noexcept {
    if (this != &other) {
        if (client_fd_ >= 0) {
            // Close existing client_fd_ before taking ownership of new one
            close(client_fd_);
            LOG_INFO(format_identity(Constants::Role::Client, client_fd_) + " closed");
        }
        
        client_fd_ = other.client_fd_;
        other.client_fd_ = -1;
    }
    
    return *this;
}

int Connection::get_client_fd() const {
    return client_fd_;
}

int Connection::release_client_fd() {
    int temp = client_fd_;
    client_fd_ = -1;
    return temp;
}

std::string Connection::receive_message() {
    char buffer[Constants::buffer_size] = {0}; // Initializes all elements to null characters '\0'
    ssize_t bytes_received = recv(client_fd_, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received <= 0) {
        LOG_INFO(format_identity(Constants::Role::Client, client_fd_) + " failed to receive data or client disconnected.");
        return "";
    }
    
    return std::string(buffer, bytes_received);
}

void Connection::send_message(std::string &message) {
    send(client_fd_, message.c_str(), message.size(), 0);
}
