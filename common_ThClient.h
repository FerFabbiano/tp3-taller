#include <iostream>
#include <string>
#include <sstream>

class ThClient{
private: 
    std::string buffer_send;
    std::string buffer_recv;
    bool continue_playing;
public: 
    ThClient();
    void read_stdin();
    void encode_command(std::string message);
    ~ThClient();
};
