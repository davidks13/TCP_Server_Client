#include <iostream>
#include <string>
#include <netdb.h>

class Client {
    public:
        Client(const int& port);
        ~Client();
        void launch_client();
        int get_socket();
    private:
        const char* server_ip;
        int port;
        struct sockaddr_in server_address;
        int client_socket;
        int status;
        void socket_created();
        void address_config();
        void connected();
};