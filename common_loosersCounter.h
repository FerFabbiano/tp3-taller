#ifndef LOOSERS_COUNTER_H
#define LOOSERS_COUNTER_H

#include <vector>
#include <thread>
#include <mutex>

class LoosersCounter {
private:
    std::mutex m;        
    unsigned int counter; 
public:
    /* Constructor */
    LoosersCounter();
    /* Incremento el valor del atributo counter */
    void inc();
    /* Obtengo la cantidad de perdedores para que el impresor pueda 
    imprimilo por pantalla. */
    int get_loosers() const;
    /* Destructor */
    ~LoosersCounter();
};

#endif
