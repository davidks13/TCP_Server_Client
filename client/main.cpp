#include "../include/functions.hpp"   
#include "../include/client.hpp"   

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong input arguments number!\n";
        return 0;
    }

    const int port = atoi(argv[1]);  // Get port number from command line argument
    Client A(port);                  // Create a Client object with the specified port

    A.launch_client();               // Launch the client and establish a connection with the server

    long prime_number;               // Variable to store the received prime number
    std::string M;                   // Variable to store user input

    while (true) {
        std::cout << "Enter a number or type q to close the connection: ";
        std::cin >> M;                // Get user input

        if (M == "q") {
            break;                    // If user enters 'q', break the loop to close the connection and exit the program
        }

        send_to_server(A.get_socket(), std::stoi(M));  // Send the user input to the server

        std::cout << "Sent\n";

        prime_number = receive_from_server(A.get_socket());  // Receive the result from the server

        if (prime_number != -1) {
            std::cout << "The M-th prime number is: " << prime_number << std::endl;
        } else {
            std::cout << "Invalid input" << std::endl;
        }
    }

    return 0;
}
