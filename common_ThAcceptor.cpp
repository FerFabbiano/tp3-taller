#include "common_ThAcceptor.h"
#include "common_ThClient.h"
#include <utility>
#include <algorithm>  
#include <string>

ThAcceptor::ThAcceptor(Socket &s, FileManager &file, WinnersCounter &winners, 
    LoosersCounter &loosers) : s(s), file(file), winners(winners),
    loosers(loosers){
        this->keep_accepting = true;
    }

ThAcceptor::~ThAcceptor(){}

void ThAcceptor::run(){
    int j = 0;
    while (keep_accepting){
        std::string num_to_guess = file.get_number();
        threads.push_back(new ThClient(accept_client(num_to_guess, winners, loosers)));
        threads[j]->start();   
        j++;
        /*
        std::vector<ThClient*> tmp;
        std::vector<ThClient*>::iterator it = threads.begin();
        int i = 0;
        for (; it != threads.end(); ++it){
            if ((*it)->is_dead()){
                (*it)->join();    
                delete *it;
                i++;
            }
            tmp.push_back(*it);
            i++;
        }
        threads.swap(tmp);
        */
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

void ThAcceptor::stop_accepting(){
    this->keep_accepting = false;
}
