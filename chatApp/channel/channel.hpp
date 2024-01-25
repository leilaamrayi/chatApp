// Channel.hpp

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

// Declaration of the Channel class
class Channel {
private:
    string channelName;           // Private member variable for the channel name
    vector<string> chatHistory;   // Private member variable for the chat history

public:
    Channel(const string& name);   // Constructor declaration taking a name parameter
    ~Channel();                    // Destructor declaration

    void sendMessage(const string& message); // Method declaration to send a message to the channel
  
    const string& getChannelName() const;     // Method declaration to get the channel name
    const vector<string>& getChatHistory() const; // Method declaration to get the chat history

    // CRUD operations
    void saveDataToFile(const string& filename) const; // Method declaration to save data to a file
    void readDataFromFile(const string& filename);      // Method declaration to read data from a file
};

#endif // CHANNEL_HPP
