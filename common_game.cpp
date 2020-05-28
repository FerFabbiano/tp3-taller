#include "common_game.h"

#define INVALID -1
#define HELP "Comandos válidos:\n\tAYUDA: despliega la lista de comandos válidos\n\tRENDIRSE: pierde el juego automáticamente\n\tXXX: Número de 3 cifras a ser enviado al servidor para adivinar el número secreto"
#define GANASTE "Ganaste"
#define PERDISTE "Perdiste"

Game::Game() : intentos(0){}

bool Game::check_if_loser(std::string answer){
    intentos ++;
    return ((intentos >= 10) && (answer != GANASTE));
}

std::string Game::compare_number(uint16_t number, std::string num_to_guess){
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
        return GANASTE;
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

Game::~Game(){}