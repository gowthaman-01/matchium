#pragma once

/**
 * @brief Creates and configures a TCP socket.
 *
 * Creates a TCP socket using the IPv4 address family and stream-based communication.
 * It also sets the SO_REUSEADDR option to ensure that the socket can be reused after program restarts.
 *
 * @throws If socket creation or configuration fails, the error-handling function is triggered.
 */
class Socket {
public:
    explicit Socket();
    ~Socket();
    
    Socket(const Socket& other) = delete;
    Socket& operator=(const Socket& other) = delete;
    
    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;
    
    [[nodiscard]] int get_fd() const;
    [[nodiscard]] int release_fd();
    
private:
    int fd_;

    void create_socket();
};



