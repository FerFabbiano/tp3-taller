#ifndef THCLIENT_H
#define THCLIENT_H

#include <string>
#include <iostream>
#include "common_socket.h"
#include "common_socket.h"

class ThClient{
public: 
    ThClient(std::string num_to_guess, Socket &s);
    ~ThClient();
    /* Recibe el comando enviado a través del socket y un entero sin signo 
    de 2 bytes. Este entero será cero en caso de que el comando enviado
    no sea un número */
    std::string set_answer(const char* command, uint16_t number);
    std::string compare_number(uint16_t number);
    void send_answer(std::string answer);
    std::string process_command();
private:
    unsigned int intentos;
    std::string help;
    std::string perdiste;
    std::string ganaste;
    std::string num_to_guess;
    Socket &s;
};


#endif
