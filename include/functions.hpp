#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

bool isPrime(int n);
long findMthPrime(int M);
int receive_from_client(int socket);
long receive_from_server(int socket);
bool send_to_client(int socket, long prime_number);
bool send_to_server(int socket, int M);

#endif