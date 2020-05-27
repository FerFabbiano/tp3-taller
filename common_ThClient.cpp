#include "common_ThClient.h"
#include <string>
#include <utility>

#define INVALID -1
#define HELP "Comandos válidos:\n\tAYUDA: despliega la lista de comandos válidos\n\tRENDIRSE: pierde el juego automáticamente\n\tXXX: Número de 3 cifras a ser enviado al servidor para adivinar el número secreto"
#define GANASTE "Ganaste"
#define PERDISTE "Perdiste"

ThClient::ThClient(std::string num_to_guess, Socket socket, WinnersCounter
    &winners, LoosersCounter &loosers) : num_to_guess(num_to_guess), 
    s(std::move(socket)), intentos(0), help(HELP), perdiste(PERDISTE), 
    ganaste(GANASTE), is_running(true), keep_reading(true), winners(winners), 
    loosers(loosers){}

ThClient::ThClient(ThClient &&other) noexcept : num_to_guess(other.num_to_guess),
    s(std::move(other.s)), intentos(0), help(HELP), perdiste(PERDISTE), 
    ganaste(GANASTE), is_running(true), keep_reading(true), winners(other.winners), 
    loosers(other.loosers){}

ThClient::~ThClient(){
    this->join();
}

std::string ThClient::set_answer(const char* command, uint16_t number){
    std::string command_recv(command);
    if (command_recv.compare("s") == 0){
        loosers.inc();
        return perdiste;
    }else if (command_recv.compare("h") == 0) {
        return help;
    }
    intentos += 1;
    std::string answer = compare_number(number); 
    if ((intentos >= 10) && (answer.compare(ganaste) != 0)){
        loosers.inc();
        return perdiste;
    }
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
        winners.inc();
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
    size_mssg_send = (answer.size());
    htons(size_mssg_send);
    s.send((char*) &size_mssg_send, sizeof(int));
    s.send(answer.data(), size_mssg_send);
}

std::string ThClient::process_command(){
    char recv_num[2], recv_command[2] = "";
    uint16_t numero = INVALID;
    s.receive(recv_command, 1);
        if (*recv_command == 'n'){
            s.receive(recv_num, 2);
            char *buff = (char*) &numero;
            for (int i = 0; i < 2; i++){
                buff[i] = recv_num[i];
            }
        }
    ntohs(numero);
    std::string rta = set_answer(recv_command, numero);
    numero = INVALID;
    return rta;
}

void ThClient::run(){
    while (keep_reading){
        std::string answer = process_command();
        send_answer(answer);
        if ((answer.compare("Ganaste") == 0) || 
        (answer.compare("Perdiste") == 0)){
            keep_reading = false;
        }
    }
    is_running = false;
}

bool ThClient::is_dead() const{
    return !is_running;
}
