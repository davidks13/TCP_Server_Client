# TCP_Server_Client

This repository contains basic server and client program, connection is made with TCP.
The server program can hold maximum of thread pool's size minus 1 clients, the server program isn't meant for large number of clients.

To compile server program go to server directory and write
```console
$ cmake -S . -B build
```
then go to /build directory and write
```console
$ make
```
server is set to go, just run it (enter port number as second argument)
```console
$ ./Server 8080
```



To compile client program go to client directory and write
```console
$ cmake -S . -B build
```
then go to /build directory and write
```console
$ make
```
client is set to go, just run it (enter port number as second argument)
```console
$ ./Client 8080
```
