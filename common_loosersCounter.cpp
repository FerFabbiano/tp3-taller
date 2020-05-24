#include "common_loosersCounter.h"

LoosersCounter::LoosersCounter() : counter(0) {}
    
void LoosersCounter::inc() {
    Lock l(m);
    counter ++;
}

void LoosersCounter::print_loosers() const{
    std::cout << "  Perdedores: " << counter << '\n';
}

LoosersCounter::~LoosersCounter(){}
