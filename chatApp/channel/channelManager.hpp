// ChannelManager.hpp

#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

#include "Channel.hpp"
#include <vector>

using std::string;

class ChannelManager {
private:
    std::vector<Channel*> channels; // Vector to store pointers to Channel objects

public:
    ChannelManager();  // Constructor declaration
    ~ChannelManager(); // Destructor declaration

    Channel* createChannel(const string& name); // Method to create a new channel
    void deleteChannel(const string& name);     // Method to delete a channel
    Channel* findChannel(const string& name) const; // Method to find a channel
    void readDataFromFile(const string& filename);  // Method to read data from files
    void printChannelHistory() const;                    // Method to print channel history
};

#endif // CHANNELMANAGER_HPP
