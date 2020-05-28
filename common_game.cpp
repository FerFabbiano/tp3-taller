#include "common_game.h"

Game::Game() : intentos(0){}

bool Game::check_if_loser(std::string answer){
    intentos ++;
    return ((intentos >= 10) && (answer.compare("Ganaste") != 0));
}

Game::~Game(){}