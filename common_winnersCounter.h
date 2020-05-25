#ifndef WINNERS_COUNTER_H
#define WINNERS_COUNTER_H

#include <vector>
#include <thread>
#include <mutex>
#include "common_lock.h"

class WinnersCounter {
private:
    std::mutex m;        
    unsigned int counter; 
public:
    /* Constructor */
    WinnersCounter();
    /* Incremento el valor del atributo resultado */
    void inc();
    /* Imprimo el valor del atributo resultado por pantalla */
    int get_winners() const;
    /* Destructor */
    ~WinnersCounter();
};

#endif
