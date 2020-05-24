#ifndef LOOSERS_COUNTER_H
#define LOOSERS_COUNTER_H

#include <vector>
#include <thread>
#include <mutex>
#include "common_lock.h"

class LoosersCounter {
private:
    std::mutex m;        
    unsigned int counter; 
public:
    /* Constructor */
    LoosersCounter();
    /* Incremento el valor del atributo resultado */
    void inc();
    /* Imprimo el valor del atributo resultado por pantalla */
    void print_loosers() const;
    /* Destructor */
    ~LoosersCounter();
};

#endif
