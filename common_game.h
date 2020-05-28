#ifndef GAME_H
#define GAME_H

#include <string>
#include "common_stats.h"

class Game{
public:
    Game(Stats &winners, Stats &losers);
    bool check_if_loser(std::string answer);
    //void init();
    ~Game();
    /* Comparo el número que ingreso el cliente, con el extraído del archivo
    de número a adivinar. En base a esa comparación, devuelvo una respuesta
    con lo que se le debe enviar al cliente. */
    std::string compare_number(uint16_t number, std::string num_to_guess);
    void surrender();
private: 
    unsigned int intentos;
    Stats &winners;
    Stats &losers;
};

#endif
