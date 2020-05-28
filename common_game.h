#ifndef GAME_H
#define GAME_H

#include <string>

class Game{
public:
    Game();
    bool check_if_loser(std::string answer);
    //void init();
    ~Game();
private: 
    unsigned int intentos;
};

#endif
