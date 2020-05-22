#include <iostream>
#include <string>
#include "common_socket.h"

#define NUM_MAX 65536

class Client{
private: 
    Socket &s;
    
    char command_send;
    char command_recv;
    uint16_t number_send;
    bool continue_playing;
    
    std::string invalid_command;
    std::string help;
    std::string surrender;
public: 
    explicit Client(Socket &s);
    void read_stdin();
    void encode_command(std::string message);
    void send_command();
    ~Client();
};
