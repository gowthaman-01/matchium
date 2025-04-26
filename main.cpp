#include "include/core/constants.hpp"
#include "include/core/utils.hpp"
#include "include/http/connection.hpp"
#include "include/http/parser.hpp"
#include "include/http/request.hpp"
#include "include/net/server_socket.hpp"

#include <iostream>
#include <string>
#include <utility>

int main() {
    Socket socket;
    ServerSocket server_socket(std::move(socket));
    
    int count = 1;
    while(true) {
        int client_fd = server_socket.accept_client();
        
        Connection conn(client_fd);
        std::string msg = conn.receive_message();
        
        Request req = parse_request(msg);
        
        // Hardcoded response
        std::string body = "Hello, world! " + std::to_string(count);
        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: "
            + std::to_string(body.size())
            + "\r\n\r\n"
            + body;
        conn.send_message(response);
        
        if (req.path == "/") {
            count++;
        }
    }
  
}
