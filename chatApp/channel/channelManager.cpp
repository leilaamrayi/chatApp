// ChannelManager.cpp

#include "ChannelManager.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

// Constructor implementation
ChannelManager::ChannelManager() {}

// Destructor implementation
ChannelManager::~ChannelManager() {
    for (auto channel : channels) {
        delete channel; // Deallocate memory for each Channel object on the heap
    }
}

// Method to create a new channel
Channel* ChannelManager::createChannel(const string& name) {
    // Create a new Channel object on the heap
    Channel* newChannel = new Channel(name);
    channels.push_back(newChannel); // Add the pointer to the new channel to the vector
    cout << "Channel '" << name << "' has been created." << endl;
    return newChannel; // Return the pointer to the newly created channel
}

// Method to delete a channel
void ChannelManager::deleteChannel(const string& name) {
    // Find the channel with the specified name in the vector
    auto it = find_if(channels.begin(), channels.end(),
                           [name](const Channel* channel) {
                               return channel->getChannelName() == name;
                           });

    if (it != channels.end()) {
        cout << "Channel '" << name << "' has been deleted." << endl;
        delete *it; // Deallocate memory for the Channel object on the heap
        channels.erase(it); // Remove the pointer from the vector
    } else {
        cerr << "Error: Channel '" << name << "' not found." << endl;
    }
}

// Method to find a channel
Channel* ChannelManager::findChannel(const string& name) const {
    // Find the channel with the specified name in the vector
    auto it = find_if(channels.begin(), channels.end(),
                           [name](const Channel* channel) {
                               return channel->getChannelName() == name;
                           });

    return (it != channels.end()) ? *it : nullptr; // Return the pointer if found, otherwise nullptr
}

// Method to read data from files and populate channel chat histories
void ChannelManager::readDataFromFile(const string& filename) {
    for (auto& channel : channels) {
        string channelFilename = filename + "_" + channel->getChannelName() + ".txt";
        ifstream inFile(channelFilename);

        if (inFile.is_open()) {
            string message;
            while (getline(inFile, message)) {
                channel->sendMessage(message); // Add each line to the channel's chat history
            }

            inFile.close();
            cout << "History loaded for channel '" << channel->getChannelName() << "'." << endl;
        } else {
            cerr << "Error opening file '" << channelFilename << "' for reading." << endl;
        }
    }
}

// Method to print the chat history of each channel
void ChannelManager::printChannelHistory() const {
    for (const auto& channel : channels) {
        cout << "Channel: " << channel->getChannelName() << endl;
        cout << "History:" << endl;
        for (const auto& message : channel->getChatHistory()) {
            cout << message << endl;
        }
        cout << "------------------------" << endl;
    }
}
