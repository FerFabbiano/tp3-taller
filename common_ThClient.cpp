#include "common_ThClient.h"

ThClient::ThClient(){
    this->invalid_num = "Número inválido. Debe ser de 3 cifras no repetidas";
    this->help = "Comandos válidos:​ \n\t​ AYUDA: despliega la lista de comandos válidos​ \n\t​ RENDIRSE: pierde el juego automáticamente​ \n\t​ XXX: Número de 3 cifras a ser enviado al servidor para adivinar el número secreto";
    this->ganaste = "Ganaste";
    this->perdiste = "Perdiste";
    this->intentos = 0;
}

ThClient::~ThClient(){}

void ThClient::set_answer(const char* command){
    std::string comando = command;
    if (comando.compare("s") == 0){
        std::cout << perdiste << std::endl;
    }else if (comando.compare("h") == 0) {
        std::cout << help << std::endl;
    }else {
        intentos += 1;
        std::cout << intentos << std::endl;
    }
}


