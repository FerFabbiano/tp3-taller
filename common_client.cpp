#include "common_client.h"
#include "common_OSError.h"

#include <string>
#include <iostream>
#include <vector>
#include <netinet/in.h>

Client::Client() : number_send(0){}

Client::~Client(){}

void Client::init(){
    bool keep_reading = true;
    while (keep_reading){
        std::string command = read_stdin();
        std::string answer;
        try{
            send_command(command);
            keep_reading = receive();
        }
        catch(std::exception &e){
            std::cout << e.what() << '\n';
        }
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
    number_send = htons(number_send);
    if (command_send == 'n'){
        s.send((char*) &number_send, 2);
    }
    command_send = ' ';
    number_send = 0;
}

bool Client::receive(){
    uint32_t length = 0;
    s.receive((char*) &length, 4);
    length = ntohl(length);
    std::vector <char> answer(length+1, 0);
    char *buf = answer.data();
    s.receive(buf, length);
    std::cout << buf << std::endl;
    return check_answer(buf);
}

bool Client::check_answer(std::string answer){
    return !((answer == "Ganaste") || (answer == "Perdiste" ));
}
