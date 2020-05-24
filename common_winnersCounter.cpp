#include "common_winnersCounter.h"

WinnersCounter::WinnersCounter() : counter(0) {}
    
void WinnersCounter::inc() {
    Lock l(m);
    counter ++;
}

void WinnersCounter::print_winners() const{
    std::cout << "  Ganadores: " << counter << '\n';
}

WinnersCounter::~WinnersCounter(){}
