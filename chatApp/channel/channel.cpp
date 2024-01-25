// Channel.cpp

#include "channel.hpp"
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;

// Constructor: Initializes the Channel with a given name.
Channel::Channel(const string& name) : channelName(name) {}

// Destructor: Cleans up resources when the Channel object is destroyed.
Channel::~Channel() {}

// Adds a message to the chat history.
void Channel::sendMessage(const string& message) {
    chatHistory.push_back(message);
 }


// Returns the name of the channel.
const std::string& Channel::getChannelName() const {
    return channelName;
}

// Returns the chat history of the channel.
const vector<string>& Channel::getChatHistory() const {
     for (const auto& message : chatHistory) {
        cout << message << endl;
    }
    return chatHistory;
}

// Saves the chat history to a file.
void Channel::saveDataToFile(const string& filename) const {
    ofstream outFile(filename.c_str()); // Use c_str() to convert string to const char*

    // Check if the file is successfully opened for writing.
    if (outFile.is_open()) {
        // Write each message in the chat history to the file.
        for (const auto& message : chatHistory) {
            outFile << message << endl;
        }
        outFile.close(); // Close the file.
        cout << "Chat history saved to file '" << filename << "'." << endl;
    } else {
        // Print an error message if the file cannot be opened.
        cerr << "Error opening file '" << filename << "' for writing." << endl;
    }
}

// Reads chat history from a file and populates the chat history vector.
void Channel::readDataFromFile(const string& filename) {
    ifstream inFile(filename);

    // Check if the file is successfully opened for reading.
    if (inFile.is_open()) {
        string message;
        // Read each line from the file and add it to the chat history.
        while (getline(inFile, message)) {
            chatHistory.push_back(message);
        }

        inFile.close(); // Close the file.
        cout << "Chat history loaded from file '" << filename << "'." << endl;
    } else {
        // Print an error message if the file cannot be opened.
        cerr << "Error opening file '" << filename << "' for reading." << endl;
    }
}

