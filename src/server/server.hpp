#pragma once

class HTTPServer {
public:
    explicit HTTPServer(int port);
    ~HTTPServer();
    void start();
    
private:
    int port_;
    int server_fd_;
    
    /**
     * @brief Sets up the server socket for listening.
     *
     * This function initializes the server’s TCP socket and prepares it to accept
     * incoming connections. It does the following:
     * - Creates a TCP socket.
     * - Configures the server address with the specified port.
     * - Binds the socket to the server address.
     * - Configures the socket to listen for incoming connections with a defined backlog.
     *
     * @throws If any step fails, it invokes the appropriate error-handling function and terminates the process.
     */
    void setup_server();
    
    /**
     * @brief Waits for an incoming client connection.
     *
     * This function blocks until a client connects to the server's listening socket.
     * When a connection is established, it returns the file descriptor for the
     * client socket, which can then be used for communication.
     *
     * @return The file descriptor for the accepted client connection.
     * @throws If accepting a connection fails, the error-handling function is invoked.
     */
    int wait_for_client();
    
    /**
     * @brief Handles communication with a connected client.
     *
     * This function receives a message from the specified client socket using `recv()`
     * and logs the content of the message.
     *
     * @param client_fd The file descriptor for the accepted client connection.
     * @throws If no data is received or an error occurs, it logs an error message.
     */
    void handle_client(int client_fd);
};
