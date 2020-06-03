#include "common_protocol.h"
#include "common_OSError.h"
#include <string>

#define INVALID_COMMAND "Error: comando inválido. Escriba AYUDA para obtener "\
"ayuda"
#define HELP "AYUDA"
#define SURRENDER "RENDIRSE"
#define NUM_MAX 65536 // 2¹⁶

Protocol::Protocol(){}

Protocol::~Protocol(){}

void Protocol::initialize(std::string command, char &command_send, 
uint16_t &number_send){
    int number = 0;
    if (command == HELP){
        command_send = 'h';
    }else if (command == SURRENDER){
        command_send = 's';
    }else {
        try {
            number = std::stoi(command, 0, 10);
        }catch(std::exception &e){
            throw OSError(INVALID_COMMAND);
        }
        if (number > NUM_MAX || number < 0){
            throw OSError(INVALID_COMMAND);
        }else{
            command_send = 'n';
            number_send = number;
        }
    }
}
