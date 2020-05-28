#ifndef WINNERS_COUNTER_H
#define WINNERS_COUNTER_H

#include <vector>
#include <thread>
#include <mutex>

class PlayersCounter {
private:
    std::mutex m;        
    unsigned int counter; 
public:
    /* Constructor */
    PlayersCounter();
    /* Incremento el valor del atributo resultado */
    void inc();
    /* Imprimo el valor del atributo resultado por pantalla */
    int get_counter() const;
    /* Destructor */
    ~PlayersCounter();
};

#endif
