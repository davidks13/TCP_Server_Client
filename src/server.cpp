#include "../include/server.hpp"

Server::Server(const int& port) : server_ip("127.0.0.1"), port(port), 
                client_sockets(std::vector<int>(0)) {}

Server::~Server() {
    for (auto& client : client_sockets) {
        close(client);
    }
    close(server_socket);
}

void Server::launch_server() {
    socket_created();
    address_config();
    bind_made();
    std::cout << "Server has been launched!" << std::endl;
}

std::vector<int> Server::get_sockets() {
    return client_sockets;
}

int Server::get_client_count() {
    return client_sockets.size();
}

void Server::socket_created() {
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_socket < 0){
        std::cerr << "socket error: " << strerror(errno) << std::endl;
        close(server_socket);
        exit(0);
    }
}

void Server::address_config() {
    memset(&server_address, 0, sizeof(sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0) {
        std::cerr << "inet_pton error: " << strerror(errno) << std::endl;
        close(server_socket);
        exit(0);
    }
}

void Server::bind_made() {
    int server_bind = bind(server_socket, (struct sockaddr*)&server_address , sizeof(server_address));
    if(server_bind < 0){
        std::cerr << "bind error: " << strerror(errno) << std::endl;
        close(server_socket);
        exit(0);
    }
}

void Server::listening() {
    if(listen(server_socket, 5) < 0){
        std::cerr << "listen error: " << strerror(errno) << std::endl;
        close(server_socket);
        exit(0);
    }
}

void Server::accepting() {
    client_socket = accept(server_socket, (struct sockaddr*)NULL, NULL);
    client_sockets.push_back(client_socket);
    if(client_socket < 0){
        std::cerr << "client_socket error: " << strerror(errno) << std::endl;
        close(client_socket);
        close(server_socket);
        exit(0);
    }
    std::cout << "Connected!\n";
}
