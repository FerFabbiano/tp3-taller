#include "common_ThClient.h"
#include <string>
#include "common_OSError.h"
#include <iostream>

ThClient::ThClient(Socket &client) : client(client){
    this->invalid_command = "Error: comando inválido. Escriba AYUDA para obtener ayuda";
    this->help = "AYUDA";
    this->surrender = "RENDIRSE";
    this->number_send = 0;
}

ThClient::~ThClient(){}

void ThClient::read_stdin(){
    std::string message;
    getline (std::cin, message);
    encode_command(message);
}

void ThClient::encode_command(std::string message){
    int number = 0;
    if (message.compare(help) == 0){
        this->command_send = 'h';
    }else if (message.compare(surrender) == 0){
        this->command_send = 's';
    }else {
        try {
            number = std::stoi(message, 0, 10);
        } catch (std::exception &e){
            throw OSError(invalid_command);
        }
        if (number > NUM_MAX){
            throw OSError(invalid_command);
        }else{
            this->command_send = 'n';
            this->number_send = number;
        }
    }
    send_command();
}

void ThClient::send_command(){
    std::cout << sizeof(command_send) << std::endl;
    std::cout << command_send << std::endl;
    std::cout << number_send << std::endl;
    client.send(&command_send, 1);
    if (command_send == 'n'){
        client.send((char*) &number_send, 2);
    }
}
