#include "common_ThClient.h"
#include <string>

ThClient::ThClient(){}

ThClient::~ThClient(){}

void ThClient::read_stdin(){
    std::string message;
    std::string quit = "q";
    getline (std::cin, message);
    while (message.compare(quit) != 0){
        encode_command(message);
        getline (std::cin, message);
    }
}

void ThClient::encode_command(std::string message){
    std::string send;
    std::string ayuda = "AYUDA";
    std::string rendirse = "RENDIRSE";
    short int number_send = 0;
    if (message.compare(ayuda) == 0){
        send = "h";
    }else if (message.compare(rendirse) == 0){
        send = "s";
    }else{
        send = "n";
        std::stringstream(message) >> number_send;
    }
    std::cout << send << number_send << std::endl;
}
