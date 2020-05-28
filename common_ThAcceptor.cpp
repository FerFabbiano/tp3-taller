#include "common_ThAcceptor.h"
#include "common_ThClient.h"
#include <utility>
#include <algorithm>  
#include <string>
#include "common_OSError.h"
#include <vector>
#include <cerrno>

ThAcceptor::ThAcceptor(FileManager &file, Stats &winners, 
    Stats &loosers) : file(file), winners(winners),
    loosers(loosers), keep_accepting(true){}

ThAcceptor::~ThAcceptor(){}

void ThAcceptor::init(const char *service){
    s.bind_and_listen(service);
}

void ThAcceptor::run(){
    while (keep_accepting){
        std::string num_to_guess = file.get_number();
        try{
            Socket socket_accepted = s.accept();
            ThClient *client = new ThClient(num_to_guess, 
            std::move(socket_accepted), winners, loosers);
            threads.push_back(client);  
            threads.back()->start();   
            delete_finish_clients(threads);
        }catch(std::exception &e){
            if (errno != 22){
                throw;
            }
        }
    }
    for (size_t i = 0; i < threads.size(); i++){
        threads.at(i)->join();    
        delete(threads.at(i));
    }
}

void ThAcceptor::stop_accepting(){
    this->keep_accepting = false;
    s.shutdown();
    s.close();
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
