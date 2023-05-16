#include "../include/pool.hpp"
#include "../include/functions.hpp"
#include "../include/server.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong input arguments number!\n";
        return 0;
    }

    const int port = atoi(argv[1]);  // Get port number from command line argument
    Server A(port);                  // Create a Server object with the specified port

    A.launch_server();               // Launch the server
    A.listening();                   // Start listening for incoming connections
    ThreadPool pool(6);              // Create a thread pool with 6 threads

    std::cout << "Waiting for connections\n";
    int client_count = 0;

    // Enqueue a task to accept incoming connections in a separate thread
    pool.Enqueue([&A]() {
        while (true) {
            A.accepting();  // Accept incoming connections
        }
    });

    while (true) {
        if (client_count < A.get_client_count()) {
            client_count = A.get_client_count();

            // Enqueue a task to handle communication with a new client
            pool.Enqueue([&A, &client_count]() {
                int client_index = client_count - 1;
                while (true) {
                    int M = receive_from_client(A.get_sockets()[client_index]);  // Receive data from the client
                    if (!M) {
                        std::cout << "Client has shutdown!" << std::endl;
                        break;
                    }
                    std::cout << "Successfully received M from " << client_index + 1
                              << " client" << std::endl;
                    send_to_client(A.get_sockets()[client_index], findMthPrime(M));  // Send result back to the client
                }
            });
        }
    }
}
