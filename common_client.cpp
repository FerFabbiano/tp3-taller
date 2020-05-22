#include "common_client.h"
#include "common_OSError.h"

#include <string>
#include <iostream>

Client::Client(Socket &s) : s(s){
    this->invalid_command = "Error: comando inválido. Escriba AYUDA para obtener ayuda";
    this->help = "AYUDA";
    this->surrender = "RENDIRSE";
    this->number_send = 0;
}

Client::~Client(){}

void Client::read_stdin(){
    std::string message;
    getline(std::cin, message);
    encode_command(message);
}

void Client::encode_command(std::string message){
    int number = 0;
    if (message.compare(help) == 0){
        this->command_send = 'h';
    }else if (message.compare(surrender) == 0){
        this->command_send = 's';
    }else {
        try {
            number = std::stoi(message, 0, 10);
        }catch(std::exception &e){
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
    command_send = ' ';
    number_send = 0;
}

void Client::send_command(){
    std::cout << "Enviando comando" << std::endl;
    s.send(&command_send, 1);
    if (command_send == 'n'){
        s.send((char*) &number_send, 2);
    }
}
