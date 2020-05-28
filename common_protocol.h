#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <string>

class Protocol{
public:
    Protocol();
    ~Protocol();
    void initialize(std::string command, char &command_send, 
    uint16_t &number_send);
};

#endif