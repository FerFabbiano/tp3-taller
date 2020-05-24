#include "common_ThAcceptor.h"
#include "common_ThClient.h"
#include <utility>
#include <string>

ThAcceptor::ThAcceptor(Socket &s, FileManager &file, WinnersCounter &winners, 
    LoosersCounter &loosers) : s(s), file(file), winners(winners),
    loosers(loosers){}

ThAcceptor::~ThAcceptor(){}

void ThAcceptor::run(){
    bool keep_running = true;
    int j = 0;
    while (keep_running){
        std::string num_to_guess = file.get_number();
        threads.push_back(new ThClient(accept_client(num_to_guess, winners, loosers)));
        threads[j]->start();   
        j++;
    }
    for (int i = 0; i < (int)threads.size(); i++){
        threads[i]->join();    
        delete(threads[i]);
    }
}

ThClient ThAcceptor::accept_client(std::string num_to_guess, WinnersCounter &winners, 
    LoosersCounter &loosers){
    Socket socket_accepted = s.accept();
    ThClient client(num_to_guess, std::move(socket_accepted), winners, loosers);
    return std::move(client);
}
