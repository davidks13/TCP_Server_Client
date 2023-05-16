#include "../include/functions.hpp"


bool isPrime(int n) {
    if (n <= 1) {
        return false;
    } 
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

long findMthPrime(int M) {
    int count = 0;
    long i = 2;
    while (count < M) {
        if (isPrime(i)){
            count++;
        } 
        if (count == M) {
            return i;
        } 
        ++i;
    }
    return -1;
}

int receive_from_client(int socket) {
    int M;
    size_t bytes_received = recv(socket, &M, sizeof(M), 0);
    if (bytes_received  == -1) {
        std::cerr << "Send error: " << strerror(errno) << std::endl;
        return 0;
    }    
    else if (bytes_received == 0) {
        close(socket);
        return 0;
    }
    return M;
}

long receive_from_server(int socket) {
    long buffer;
    size_t bytes_received = recv(socket, &buffer, sizeof(buffer), 0);
    if (bytes_received  == -1) {
        std::cerr << "Receive error: " << strerror(errno) << std::endl;
        exit(0);
    }
    return buffer;
}

bool send_to_client(int socket, long prime_number){
    long buffer = prime_number;
    size_t bytes_send = send(socket, &buffer, sizeof(buffer), 0);
    if (bytes_send  == -1) {
        std::cerr << "Send error: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool send_to_server(int socket, int M){
    int buffer = M;
    size_t bytes_send = send(socket, &buffer, sizeof(buffer), 0);
    if (bytes_send  == -1) {
        std::cout << "Send error: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}
