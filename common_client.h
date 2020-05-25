#include <iostream>
#include <string>
#include "common_socket.h"

#define NUM_MAX 65536

class Client{
private: 
    Socket &s;
    char command_send;
    uint16_t number_send;
    bool continue_playing;    
    std::string invalid_command;
    std::string help;
    std::string surrender;

public: 
    /* Constructor */
    explicit Client(Socket &s);
    /* Leo el comando ingresado por el cliente el la entrada estándar. 
    Devuelvo el comando en un string. */
    std::string read_stdin();
    /* Seteo, en base al comando que ingreso el cliente, el mensaje para
    enviarle al servidor (seteo con los valores correspondientes los atributos
    command_send y number_send) */
    void encode_command(std::string command);
    /* Envío el comando ingresado por el cliente, formateado, a través del 
    socket. En caso de haber ingresado un número, envío el comando y 
    luego envío dicho número. */
    void send_command(std::string command);
    /* Recibo la respuesta proveniente del servidor en base al comando y/o número
    enviado. */
    std::string rcv_answer();
    /* Recibo por parámetro un string. Devuelvo verdadero si no coincide con
    "ganaste" o "perdiste". Falso caso contrario. */
    bool check_answer(std::string answer);
    /* Destructor */
    ~Client();
};
