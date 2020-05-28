#include "common_winnersCounter.h"

WinnersCounter::WinnersCounter() : counter(0) {}
    
void WinnersCounter::inc() {
    std::unique_lock<std::mutex> lk(this->m);
    counter ++;
}

int WinnersCounter::get_winners() const{
    return counter;
}

WinnersCounter::~WinnersCounter(){}
