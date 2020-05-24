#include "common_ThClient.h"

#define INVALID -1

ThClient::ThClient(std::string num_to_guess, Socket socket) : 
    num_to_guess(num_to_guess), s(std::move(socket)){
    this->help = "Comandos válidos:​ \n\t​ AYUDA: despliega la lista de comandos válidos​ \n\t​ RENDIRSE: pierde el juego automáticamente​ \n\t​ XXX: Número de 3 cifras a ser enviado al servidor para adivinar el número secreto";
    this->ganaste = "Ganaste";
    this->perdiste = "Perdiste";
    this->intentos = 0;
    this->is_running = true;
}

ThClient::ThClient(ThClient &&other) noexcept : s(std::move(other.s)){
    this->help = "Comandos válidos:​ \n\t​ AYUDA: despliega la lista de comandos válidos​ \n\t​ RENDIRSE: pierde el juego automáticamente​ \n\t​ XXX: Número de 3 cifras a ser enviado al servidor para adivinar el número secreto";
    this->ganaste = "Ganaste";
    this->perdiste = "Perdiste";
    this->intentos = 0;
    this->is_running = true;
    this->num_to_guess = other.num_to_guess;
}


ThClient::~ThClient(){}

std::string ThClient::set_answer(const char* command, uint16_t number){
    std::string comando = command;
    if (comando.compare("s") == 0){
        return perdiste;
    }else if (comando.compare("h") == 0) {
        return help;
    }
    intentos += 1;
    std::string answer = compare_number(number); 
    if ((intentos >= 10) && (answer.compare(ganaste) != 0))
        return perdiste;
    return answer;
}


std::string ThClient::compare_number(uint16_t number){
    std::string answer, num = std::to_string(number);
    int bien = 0, regular = 0;
    if (((number < 100) ||  (number > 999)) && (number != INVALID)){
        answer = "Número inválido. Debe ser de 3 cifras no repetidas";
        return answer;
    }
    if ((num[0] == num [1]) || (num[0] == num[2]) || (num[1] == num[2])){
        answer = "Número inválido. Debe ser de 3 cifras no repetidas";
        return answer;          
    }
    if (num.compare(num_to_guess) == 0){
        return ganaste;
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

void ThClient::send_answer(std::string answer){
    unsigned int size_mssg_send = 0;
    size_mssg_send = answer.size();
    s.send((char*) &size_mssg_send, sizeof(int));
    s.send(answer.data(), size_mssg_send);
}

std::string ThClient::process_command(){
    char recv_num[2], recv_command[2];
    uint16_t numero = INVALID;
    s.receive(recv_command, 1);
        if (*recv_command == 'n'){
            s.receive(recv_num, 2);
            numero = *(uint16_t*) recv_num;
        }
    std::string rta = set_answer(recv_command, numero);
    numero = INVALID;
    return rta;
}

void ThClient::run(){
    bool keep_reading = true;
    while (keep_reading){
        std::string answer = process_command();
        send_answer(answer);
        if ((answer.compare("Ganaste") == 0) || (answer.compare("Perdiste") == 0)){
            keep_reading = false;
            is_running = false;
        }
    }
}

bool ThClient::is_dead(){
    return is_running;
}
