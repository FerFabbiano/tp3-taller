#include <iostream>
#include <string>
#include <sstream>
#include "common_socket.h"

#define NUM_MAX 65536

class ThClient{
private: 
    char command_send;
    char command_recv;
    uint16_t number_send;
    bool continue_playing;
    Socket &client;
public: 
    ThClient(Socket &client);
    void read_stdin();
    void encode_command(std::string message);
    ~ThClient();
};
