#include "common_ThAcceptor.h"
#include "common_ThClient.h"

ThAcceptor::ThAcceptor(Socket &s, FileManager &file) : s(s), file(file){}

ThAcceptor::~ThAcceptor(){}

void ThAcceptor::run(){
    bool keep_running = true;
    int j = 0;
    Socket socket_accept = s.accept();
    while (keep_running){
        std::string num_to_guess = file.get_number();
        threads.push_back(new ThClient(num_to_guess, socket_accept));
        threads[j]->start();   
        j++;
        socket_accept = s.accept();
    }
    for (int i = 0; i < (int)threads.size(); i++){
        threads[i]->join();    
        delete(threads[i]);
    }
}
