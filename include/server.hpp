#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <netdb.h>
#include <queue>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

class Server {
    public:
        Server(const int& port);
        ~Server();
        void launch_server();
        std::vector<int> get_sockets();
        int get_socket();
        void listening();
        void accepting();
        int get_client_count();
    private:
        const char* server_ip;
        int port;
        int server_socket;
        struct sockaddr_in server_address;
        std::vector<int> client_sockets;
        int client_socket;
        void socket_created();
        void address_config();
        void bind_made();
};

#endif