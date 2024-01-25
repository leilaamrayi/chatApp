// main.cpp
#include "server/Server.hpp"
#include "channel/ChannelManager.hpp"
#include <iostream>
#include <thread>
#include <string>

using std::cout;
using std::cerr;
using std::endl;


// Simulate a chat scenario with channels
void simulateChatScenario(ChannelManager& channelManager) {
    // Simulate sending messages to the channel after some delay
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Create two channels
    Channel* generalChannel = channelManager.createChannel("General");
    Channel* newsChannel = channelManager.createChannel("News");

    // Send messages to a news channel
    
    newsChannel->sendMessage("Breaking news: Something interesting happened!");
    newsChannel->sendMessage("Stay tuned for more updates!");

    // Switch to the General channel
    Channel* switchedChannel = channelManager.findChannel("General");

    if (switchedChannel) {
        // If General channel found, switch and add more messages
        cout << "-----Switching to the General channel.-----" << endl;
        cout << "-----Sending messages to the General channel.-----" << endl;
        switchedChannel->sendMessage("Hello, this is a test message in General channel!");
        switchedChannel->sendMessage("How is everyone doing?");

        // Display chat history for the General channel
        switchedChannel->getChatHistory();
    } else {
        // Error: General channel not found
        cerr << "Error: General channel not found." << endl;
    }
    
    // Save and read data from files for both channels
    generalChannel->saveDataToFile("generaChannelHistory.txt");
    newsChannel->saveDataToFile("newsChannelHistory.txt");

    // Delete the News channel
    channelManager.deleteChannel("News");
}

// Demonstrate channel operations, e.g., deleting a channel
void demonstrateChannelOperations(ChannelManager& channelManager) {
    // Delete the General channel
    channelManager.deleteChannel("News");
}


// Main function
int main() {
    // Initialize server
    server server;
    server.startListening();

    // Create a channel manager
    ChannelManager channelManager;

    // Simulate a chat scenario in two channels
    simulateChatScenario(channelManager);

    return 0;
}
