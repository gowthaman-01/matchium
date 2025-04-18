#include "src/core/constants.hpp"
#include "src/http/connection.hpp"
#include "src/http/parser.hpp"
#include "src/http/request.hpp"
#include "src/net/server_socket.hpp"

#include "src/core/utils.hpp"

#include <iostream>
#include <string>
#include <utility>

int main() {
    Socket socket;
    
    ServerSocket server_socket(std::move(socket));
    int client_fd = server_socket.accept_client();
    
    Connection conn(client_fd);
    std::string msg = conn.receive_message();
    
    Request req = parse_request(msg);
    
    // Hardcoded response
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "Hello, world!";
    conn.send_message(response);
}
