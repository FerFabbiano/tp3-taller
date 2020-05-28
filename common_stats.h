#ifndef WINNERS_COUNTER_H
#define WINNERS_COUNTER_H

#include <vector>
#include <thread>
#include <mutex>

class Stats {
private:
    std::mutex m;        
    unsigned int counter; 
public:
    /* Constructor */
    Stats();
    /* Incremento el valor del atributo resultado */
    void inc();
    /* Imprimo el valor del atributo resultado por pantalla */
    int get_counter() const;
    void operator()(int winners, int losers);
    /* Destructor */
    ~Stats();
};

#endif
