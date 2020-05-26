#include "common_ThAcceptor.h"
#include "common_ThClient.h"
#include <utility>
#include <algorithm>  
#include <string>
#include "common_OSError.h"
#include <vector>

ThAcceptor::ThAcceptor(Socket &s, FileManager &file, WinnersCounter &winners, 
    LoosersCounter &loosers) : s(s), file(file), winners(winners),
    loosers(loosers){
        this->keep_accepting = true;
        this->push = true;
    }

ThAcceptor::~ThAcceptor(){}

void ThAcceptor::run(){
    while (keep_accepting){
        std::string num_to_guess = file.get_number();
        ThClient *client = new ThClient(accept_client(num_to_guess, 
        winners, loosers));
        if (push){    
            threads.push_back(client);  
            threads.back()->start();   
            delete_finish_clients(threads);
        }
        if (!push)
            delete(client);
    }
    for (int i = 0; i < (int)threads.size(); i++){
        threads.at(i)->join();    
        delete(threads.at(i));
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

void ThAcceptor::delete_finish_clients(std::vector<ThClient*> &threads){
    std::vector<ThClient*> temp;
    std::vector<ThClient*>::iterator it = threads.begin();
    for (; it != threads.end(); ++it){    
        if ((*it)->is_dead()){
            (*it)->join();   
            delete(*it);
        }else{
            temp.push_back(*it);
        }
    }  
    threads.swap(temp);
}
