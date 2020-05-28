#include "common_client.h"
#include "common_OSError.h"

#include <string>
#include <iostream>
#include <vector>

Client::Client() : number_send(0){}

Client::~Client(){}

void Client::init(){
    bool keep_reading = true;
    while (keep_reading){
        std::string command = read_stdin();
        std::string answer;
        try{
            send_command(command);
            answer = receive();
        }
        catch(std::exception &e){
            std::cout << e.what() << '\n';
        }
        keep_reading = check_answer(answer);
    }
}

void Client::connect(const char *host_name, const char *service){
    s.connect(host_name, service);
}

std::string Client::read_stdin(){
    std::string command;
    std::cin >> command;
    return command;
}

void Client::send_command(std::string command){
    char command_send;
    uint16_t number_send;
    protocol.initialize(command, command_send, number_send);
    s.send(&command_send, 1);
    htons(number_send);
    if (command_send == 'n'){
        s.send((char*) &number_send, 2);
    }
    command_send = ' ';
    number_send = 0;
}

std::string Client::receive(){
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
    return !((answer == "Ganaste") || (answer == "Perdiste" ));
}
