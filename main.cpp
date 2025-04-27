#include "include/core/constants.hpp"
#include "include/http/connection.hpp"
#include "include/http/parser.hpp"
#include "include/http/request.hpp"
#include "include/http/router.hpp"
#include "include/http/handlers/snapshot_handler.hpp"
#include "include/net/server_socket.hpp"

#include <iostream>
#include <string>
#include <utility>

int main() {
    Socket socket;
    ServerSocket server_socket(std::move(socket));
    
    Router router;
    router.register_handler(Constants::GET_METHOD, Constants::SNAPSHOT_PATH, snapshot_handler);

    while(true) {
        int client_fd = server_socket.accept_client();
        Connection conn(client_fd);
        
        std::string raw_msg = conn.receive_message();
        Request req = Parser::parse_request(raw_msg);
        
        Response res = router.route(req);
        std::string raw_response = Parser::serialise_response(res);
        
        conn.send_message(raw_response);
    }
}
 
