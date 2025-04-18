#include <string>

/**
 * @brief Represents a client connection to the server.
 *
 * Manages the lifecycle of a connected socket (client_fd) and provides
 * functionality to receive the HTTP request message from the client.
 * Automatically closes the connection on destruction unless released.
 */
class Connection {
public:
    explicit Connection(int client_fd);
    ~Connection();
    
    Connection(const Connection& other) = delete;
    Connection& operator=(const Connection& other) = delete;
    
    Connection(Connection&& other) noexcept;
    Connection& operator=(Connection&& other) noexcept;
    
    [[nodiscard]] int get_client_fd() const;
    [[nodiscard]] int release_client_fd();
    
    [[nodiscard]] std::string receive_message();
    void send_message(std::string& message);
    
private:
    int client_fd_;
};
