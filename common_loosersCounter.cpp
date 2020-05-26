#include "common_loosersCounter.h"

LoosersCounter::LoosersCounter() : counter(0) {}
    
void LoosersCounter::inc() {
    Lock l(m);
    counter ++;
}

int LoosersCounter::get_loosers() const{
    return counter;
}

LoosersCounter::~LoosersCounter(){}
