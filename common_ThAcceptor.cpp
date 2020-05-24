#include "common_ThAcceptor.h"
#include "common_ThClient.h"
#include <utility>

ThAcceptor::ThAcceptor(Socket &s, FileManager &file) : s(s), file(file){}

ThAcceptor::~ThAcceptor(){}

void ThAcceptor::run(){
    bool keep_running = true;
    int j = 0;
    while (keep_running){
        std::string num_to_guess = file.get_number();
        threads.push_back(new ThClient(accept_client(num_to_guess)));
        threads[j]->start();   
        j++;
    }
    for (int i = 0; i < (int)threads.size(); i++){
        threads[i]->join();    
        delete(threads[i]);
    }
}

ThClient ThAcceptor::accept_client(std::string num_to_guess){
    Socket socket_accepted = s.accept();
    ThClient client(num_to_guess, std::move(socket_accepted));
    return std::move(client);
}
