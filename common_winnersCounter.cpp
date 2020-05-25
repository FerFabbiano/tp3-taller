#include "common_winnersCounter.h"

WinnersCounter::WinnersCounter() : counter(0) {}
    
void WinnersCounter::inc() {
    Lock l(m);
    counter ++;
}

int WinnersCounter::get_winners() const{
    return counter;
}

WinnersCounter::~WinnersCounter(){}
