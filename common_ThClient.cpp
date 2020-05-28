#include "common_ThClient.h"
#include <string>
#include <utility>
#include <netinet/in.h>

#define INVALID -1
#define HELP "Comandos válidos:\n\tAYUDA: despliega la lista de comandos válidos\n\tRENDIRSE: pierde el juego automáticamente\n\tXXX: Número de 3 cifras a ser enviado al servidor para adivinar el número secreto"
#define GANASTE "Ganaste"
#define PERDISTE "Perdiste"
#define SIZE_OF_INT 4

ThClient::ThClient(std::string num_to_guess, Socket socket, Stats
    &winners, Stats &loosers) : num_to_guess(num_to_guess), 
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
    if (strncmp(command, "s", 1) == 0){
        loosers.inc();
        return perdiste;
    }else if (strncmp(command, "h", 1) == 0) {
        return help;
    }
    intentos += 1;
    std::string answer = game.compare_number(number, num_to_guess); 
    if (answer == GANASTE){
        winners.inc();
    }
    if ((intentos >= 10) && (answer != GANASTE)){
        loosers.inc();
        return PERDISTE;
    }
    return answer;
}

void ThClient::send_answer(std::string answer){
    uint32_t size_mssg_send = htonl(answer.size());
    s.send((char*) &size_mssg_send, SIZE_OF_INT);
    s.send(answer.data(), answer.size());
}

std::string ThClient::process_command(){
    char recv_command = ' ';
    uint16_t numero = INVALID;
    s.receive(&recv_command, 1);
        if (recv_command == 'n'){
            s.receive((char*) &numero, 2);
            numero = ntohs(numero);
        }
    std::string rta = set_answer(&recv_command, numero);
    numero = INVALID;
    return rta;
}

void ThClient::run(){
    while (keep_reading){
        std::string answer = process_command();
        send_answer(answer);
        if ((answer == ("Ganaste")) || 
        (answer == ("Perdiste"))){
            keep_reading = false;
        }
    }
    is_running = false;
}

bool ThClient::is_dead() const{
    return !is_running;
}
