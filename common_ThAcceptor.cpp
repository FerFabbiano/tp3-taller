#include "common_ThAcceptor.h"
#include "common_ThClient.h"
#include <utility>
#include <algorithm>  
#include <string>
#include "common_OSError.h"

ThAcceptor::ThAcceptor(Socket &s, FileManager &file, WinnersCounter &winners, 
    LoosersCounter &loosers) : s(s), file(file), winners(winners),
    loosers(loosers){
        this->keep_accepting = true;
        this->push = true;
    }

ThAcceptor::~ThAcceptor(){}

void ThAcceptor::run(){
    int j = 0;
    while (keep_accepting){
        std::string num_to_guess = file.get_number();
        ThClient *client = new ThClient(accept_client(num_to_guess, 
        winners, loosers));
        if (push){
            threads.push_back(client);      
            threads[j]->start();   
            j++;
            for (int i = 0; i < (int)threads.size(); i++){
                if (threads[i]->is_dead()){
                    threads[i]->join();
                    delete threads[i];   
                    threads.erase(std::remove_if(threads.begin(), threads.end(),
                    [](const ThClient* client) {return client->is_dead(); })
                    , threads.end());
                    j--;
                }
            }
        }
        if (!push)
            delete client;
    }
    for (int i = 0; i < (int)threads.size(); i++){
        threads[i]->join();    
        delete(threads[i]);
    }
}

ThClient ThAcceptor::accept_client(std::string num_to_guess,
    WinnersCounter &winners, LoosersCounter &loosers){
    Socket socket_accepted = s.accept();
    ThClient client(num_to_guess, std::move(socket_accepted), winners, loosers);
    return std::move(client);
}

void ThAcceptor::stop_accepting(){
    this->keep_accepting = false;
    this->push = false;
}
