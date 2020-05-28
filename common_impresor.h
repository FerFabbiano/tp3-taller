#ifndef IMPRESOR_H
#define IMPRESOR_H

#include <iostream>

class Impresor {
public: 
    /* El operador llamada a función me permite tratar a la clase como 
    si fuera una función. */
    void operator()(int winners, int losers);
};

#endif
