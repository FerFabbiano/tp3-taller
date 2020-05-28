#include <iostream>
#include "common_stats.h"

Stats::Stats() : counter(0) {}
    
void Stats::inc() {
    std::unique_lock<std::mutex> lk(this->m);
    counter ++;
}

int Stats::get_counter() const{
    return counter;
}

void Stats::operator()(int winners, int losers){
    std::cout << "Estadísticas:\n\tGanadores:  " << winners << '\n'
    << "\tPerdedores: " << losers << '\n';
}

Stats::~Stats(){}
