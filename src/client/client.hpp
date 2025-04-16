#pragma once

#include <string_view>

class Client {
public:
    explicit Client(int port);
    ~Client();
    void start();
    void send_message(const std::string_view& message);
    
private:
    int port_;
    int client_fd_;
    
    void connect_to_server();
    
    
};
