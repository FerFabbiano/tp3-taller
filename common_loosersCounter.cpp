#include "common_loosersCounter.h"

LoosersCounter::LoosersCounter() : counter(0) {}
    
void LoosersCounter::inc() {
    std::unique_lock<std::mutex> lk(this->m);
    counter ++;
}

int LoosersCounter::get_loosers() const{
    return counter;
}

LoosersCounter::~LoosersCounter(){}
