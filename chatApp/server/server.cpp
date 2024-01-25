// Server.cpp

#include "Server.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using std::cout;
using std::cerr;
using std::endl;

// Constructor: initializes the server by calling the startup function
server::server() {
    serverSocket = startup();
}

// Destructor: closes the server socket when the object is destroyed
server::~server() {
    closesocket(serverSocket);
}

// Function to set up the server socket and return it
SOCKET server::startup() {
    WSAData wsaData;
    SOCKET serverSocket;
    sockaddr_in sockAddr;

    // Initialize Windows Sockets
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
        exitEnv(10, "Error starting the Windows socket service");
    }

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET) {
        // Error: Failed to create a server socket
        exitEnv(11, "Error creating server socket");
    }

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(settings.addr.c_str());
    sockAddr.sin_port = htons(settings.port);

    // Bind the socket to a specific address and port
    if (bind(serverSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
        // Error: Failed to bind the server socket
        exitEnv(12, "Error binding the server socket");
    }

    // Start listening for incoming connections
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        // Error: Failed to start listening with the server socket
        exitEnv(13, "Error listening with the server socket");
    }

    return serverSocket;
}

// Function to handle incoming client connections and messages in a separate thread
void server::serverThreadFunction() {
    SOCKET clientSocket;
    cout << "Server is listening on port " << settings.port << endl;

    while (true) {
        // Accept a connection from a client
        clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            // Error: Failed to accept the client connection
            cerr << "Error accepting client connection." << endl;
            continue; // Continue to the next iteration of the loop
        }

        cout << "Client connected on port " << settings.port << endl;

        string message;
        char recMessage[256];
        int size = -1;

        // Receive data from the client
        do {
            size = recv(clientSocket, recMessage, 256, 0);
            if (size > 0) {
                recMessage[size] = '\0';
                message.append(recMessage);
            }
        } while (size == 256);

        if (size == SOCKET_ERROR) {
            // Error: Failed to receive data from the client
            cerr << "Error receiving data from the client." << endl;
        } else {
            std::cout << message << std::endl;
        }

        // Close the client socket
        closesocket(clientSocket);
    }
}

// Function to start the server thread (detached for background execution)
void server::startListening() {
    std::thread serverThread(&server::serverThreadFunction, this);
    serverThread.detach(); // Detach the thread to let it run in the background
}
