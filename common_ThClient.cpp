#include "common_ThClient.h"
#include <string>
#include "common_OSError.h"

ThClient::ThClient(Socket &client) : number_send(0), client(client){}

ThClient::~ThClient(){}

void ThClient::read_stdin(){
    std::string message;
    getline (std::cin, message);
    encode_command(message);
}

void ThClient::encode_command(std::string message){
    std::string ayuda = "AYUDA";
    std::string rendirse = "RENDIRSE";
    std::string error = "Error: comando inválido. Escriba AYUDA para obtener ayuda";
    int number = 0;
    if (message.compare(ayuda) == 0){
        this->command_send = 'h';
        client.send(&command_send, 1);
    }else if (message.compare(rendirse) == 0){
        this->command_send = 's';
        client.send(&command_send, 1);
    }else {
        try {
            number = std::stoi(message, 0, 10);
        } catch (std::exception &e){
            throw OSError(error);
        }
        if (number > NUM_MAX){
            this->number_send = 0;
            throw OSError(error);
        }else{
            this->command_send = 'n';
            client.send(&command_send, 1);
            this->number_send = number;
        }
    }
}
