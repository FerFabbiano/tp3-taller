#include "common_client.h"
#include "common_OSError.h"

#include <string>
#include <iostream>
#include <vector>

Client::Client(Socket &s) : s(s){
    this->invalid_command = "Error: comando inválido."
    "Escriba AYUDA para obtener ayuda";
    this->help = "AYUDA";
    this->surrender = "RENDIRSE";
    this->number_send = 0;
}

Client::~Client(){}

std::string Client::read_stdin(){
    std::string command;
    std::cin >> command;
    return command;
}

void Client::encode_command(std::string command){
    int number = 0;
    if (command.compare(help) == 0){
        this->command_send = 'h';
    }else if (command.compare(surrender) == 0){
        this->command_send = 's';
    }else {
        try {
            number = std::stoi(command, 0, 10);
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
}

void Client::send_command(std::string command){
    encode_command(command);
    s.send(&command_send, 1);
    if (command_send == 'n'){
        s.send((char*) &number_send, 2);
    }
    command_send = ' ';
    number_send = 0;
}

std::string Client::rcv_answer(){
    char string_length[4];
    s.receive(string_length, sizeof(string_length));
    int length = 0;
    char *buff = (char*) &length;
    for (int i = 0; i < 4; i++){
        buff[i] = string_length[i];
    }
    std::vector <char> answer(length+1, 0);
    char *buf = answer.data();
    s.receive(buf, length);
    std::cout << buf << std::endl;
    return buf;
}

bool Client::check_answer(std::string answer){
    if ((answer.compare("Ganaste") == 0) || (answer.compare("Perdiste") == 0))
        return false;
    return true;
}

