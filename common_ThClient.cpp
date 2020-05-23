#include "common_ThClient.h"

ThClient::ThClient(std::string num_to_guess) : num_to_guess(num_to_guess){
    this->help = "Comandos válidos:​ \n\t​ AYUDA: despliega la lista de comandos válidos​ \n\t​ RENDIRSE: pierde el juego automáticamente​ \n\t​ XXX: Número de 3 cifras a ser enviado al servidor para adivinar el número secreto";
    this->ganaste = "Ganaste";
    this->perdiste = "Perdiste";
    this->intentos = 0;
}

ThClient::~ThClient(){}

void ThClient::set_answer(const char* command, uint16_t number){
    std::string comando = command;
    if (comando.compare("s") == 0){
        std::cout << perdiste << std::endl;
        std::cout << sizeof(perdiste) << std::endl;
    }else if (comando.compare("h") == 0) {
        std::cout << help << std::endl;
        std::cout << sizeof(help) << std::endl;
    }else {
        intentos += 1;
        std::string answer = compare_number(number); 
        std::cout << answer  << std::endl;
        std::cout << sizeof(answer);
    }
}

std::string ThClient::compare_number(uint16_t number){
    std::string answer;
    std::string num = std::to_string(number);
    int bien = 0, regular = 0;
    if ((number < 100) ||  (number > 999)){
        answer = "Número inválido. Debe ser de 3 cifras no repetidas";
        return answer;
    }
    if ((num[0] == num [1]) || (num[0] == num[2]) || 
        (num[1] == num[2])){
        answer = "Número inválido. Debe ser de 3 cifras no repetidas";
        return answer;          
    }
    if (num.compare(num_to_guess) == 0){
        return ganaste;
        //sumar 1 al contador de ganadores
    }
    for (int i = 0; i < 3; i++){
        if (num[i] == num_to_guess[i])
            bien ++;
        for (int j = 0; j < 3; j ++){
            if ((num[i] == num_to_guess[j]) && (i != j))
                regular ++;
        }
    }
    if ((bien == 0) && (regular == 0))
        answer = "3 mal";
    if ((bien != 0) && (regular == 0))
        answer = std::to_string(bien) + " bien";
    if (bien == 0 && regular != 0)
        answer = std::to_string(regular) + " regular";
    if ((bien != 0) && (regular != 0)){
        answer = std::to_string(bien) + " bien, " + std::to_string(regular) 
            + " regular";
    }
    return answer;
}


