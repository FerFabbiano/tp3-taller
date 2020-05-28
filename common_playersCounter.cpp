#include "common_playersCounter.h"

PlayersCounter::PlayersCounter() : counter(0) {}
    
void PlayersCounter::inc() {
    std::unique_lock<std::mutex> lk(this->m);
    counter ++;
}

int PlayersCounter::get_counter() const{
    return counter;
}

PlayersCounter::~PlayersCounter(){}
