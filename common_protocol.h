#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <string>

class Protocol{
public:
    /* Constructor */
    Protocol();
    /* Destructor */
    ~Protocol();
    /* Inicializo protocolo para enviar a través del socket. Recibo por 
    parámetro el comando ingresado por el cliente- En base a este y seteo 
    con los valores correctos los otro dos parámetros para que queden listos
    para enviar. */
    void initialize(std::string command, char &command_send, 
    uint16_t &number_send);
};

#endif
