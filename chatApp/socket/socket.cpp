// socket.cpp

#include <iostream>
#include "socket.hpp"

using std::cerr;
using std::endl;
using std::string;

// Function to handle socket errors and perform cleanup
inline void handleSocketError(int status, string error) {
    cerr << error << endl;
    WSACleanup();  // Clean up Windows Sockets API
    exit(status);  // Exit the program with the specified status
}

// Function to handle unexpected socket errors
inline void ehandleSocketError(int status) {
    handleSocketError(status, "Unexpected error");
}

// Constructor for the Socket class
Socket::Socket() {
    // Initialize Windows Sockets
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
        handleSocketError(10, " socket connection problem ");
    }

    // Create a socket
    mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (mSocket == INVALID_SOCKET) {
        handleSocketError(11, " invalid socket ");
    }
}

// Destructor for the Socket class
Socket::~Socket() {
    closesocket(mSocket);  // Close the socket
}

// Constructor for the NetSocket class, derived from Socket
NetSocket::NetSocket(string netAddr, int port) : Socket() {
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(netAddr.c_str());
    addr.sin_port = htons(port);
}

// Constructor for the ServerSocket class, derived from NetSocket
ServerSocket::ServerSocket(string netAddr, int port) : NetSocket(netAddr, port), bufferSize(256) {
    // Bind the socket
    if (bind(getSocket(), (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        handleSocketError(12, "Error caused by failure in binding socket instance");
    }

    // Listen for incoming connections
    if (listen(getSocket(), 1) == SOCKET_ERROR) {
        handleSocketError(13, "Error caused by failure in listening to the socket instance");
    }
}

// Destructor for the ServerSocket class
ServerSocket::~ServerSocket() {
    // Close connections for all clients
    while (!clients.empty()) {
        closeConnection(clients.back());
    }
}

// Function to wait for a client to connect
bool ServerSocket::awaitClient(SOCKET &client) {
    // Accept a client connection
    client = accept(getSocket(), NULL, NULL);

    if (client == INVALID_SOCKET) {
        handleSocketError(14, "Error accepting client connection");
        return false;
    }

    clients.push_back(client);
    return true;
}

// Function to receive data from a client
int ServerSocket::receive(SOCKET& client) {
    char* package = new char[bufferSize];
    int size = recv(client, package, bufferSize, 0);

    if (size == SOCKET_ERROR) {
        handleSocketError(15, "Error receiving data from client");
    } else if (size > 0) {
        package[size] = '\0';
        message.append(package);
    }

    delete[] package;

    return size;
}

// Function to get the size of the stored message
int ServerSocket::getMessageSize() {
    return message.length();
}

// Function to retrieve data from a client
string ServerSocket::retrieveData(SOCKET &client) {
    int size = -1;
    string data;

    do {
        size = receive(client);
    } while (size == bufferSize);

    data = message.substr(0);
    message.clear();

    return data;
}

// Function to close a client connection
void ServerSocket::closeConnection(SOCKET &client) {
    int index = 0;
    bool found = false;

    // Find the index of the client in the vector
    while (index < clients.size() && !found) {
        if (clients.at(index) == client) {
            found = true;
        } else {
            index++;
        }
    }

    if (found) {
        // Close the client socket
        if (closesocket(clients.at(index)) == SOCKET_ERROR) {
            handleSocketError(16, "Error closing client connection");
        }

        // Remove the client from the vector
        clients.erase(clients.begin() + index);
    }
}
