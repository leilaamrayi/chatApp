// server.hpp

#ifndef SERVER_HPP
#define SERVER_HPP

#include <winsock2.h>   // Include the Windows Sockets API
#include <iostream>     // Include I/O stream functionalities
#include <string>       // Include string handling
#include <thread>       // Include thread support

using std::string;      // Using directive to bring the string type into scope
using std::cerr;        // Using directive to bring cerr into scope
using std::endl;        // Using directive to bring endl into scope

// Structure to hold server settings
struct ServerSettings {
    int port;            // Port number for the server
    string addr;         // IP address for the server
};

// Declaration of the external variable for server settings
extern ServerSettings settings;

// Inline function to handle environment exit with cleanup
inline void exitEnv(int status, string msg) {
    cerr << msg << endl;    // Print error message to cerr
    WSACleanup();           // Clean up Windows Sockets API
    exit(status);           // Exit the program with the specified status
}

// Class representing a server
class server {
public:
    // Constructor: initializes the server by calling the startup function
    server();

    // Destructor: closes the server socket when the object is destroyed
    ~server();

    // Function to start listening for incoming connections in a separate thread
    void startListening();

private:
    // Function to set up the server socket and return it
    SOCKET startup();

    // Function representing the server thread logic
    void serverThreadFunction();

    SOCKET serverSocket;    // Socket for the server
};

#endif // SERVER_HPP
