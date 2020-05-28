#ifndef GAME_H
#define GAME_H

#include <string>

class Game{
public:
    Game();
    bool check_if_loser(std::string answer);
    //void init();
    ~Game();
    /* Comparo el número que ingreso el cliente, con el extraído del archivo
    de número a adivinar. En base a esa comparación, devuelvo una respuesta
    con lo que se le debe enviar al cliente. */
    std::string compare_number(uint16_t number, std::string num_to_guess);
private: 
    unsigned int intentos;
};

#endif
