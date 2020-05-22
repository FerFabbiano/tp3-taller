#ifndef THCLIENT_H
#define THCLIENT_H

#include <string>
#include <iostream>
#include "common_socket.h"

class ThClient{
public: 
    ThClient();
    ~ThClient();
    void set_answer(const char* command);

private:
    std::string invalid_num;
    unsigned int intentos;
    std::string help;
    std::string perdiste;
    std::string ganaste;
};


#endif
