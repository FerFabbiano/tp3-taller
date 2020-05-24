#ifndef THACCEPTOR_H
#define THACCEPTOR_H

#include "common_thread.h"
#include <vector>
#include "common_socket.h"
#include "common_fileManager.h"
#include <string>
#include "common_ThClient.h"
#include "common_loosersCounter.h"
#include "common_winnersCounter.h"

class ThAcceptor : public Thread{
public:
    ThAcceptor(Socket &s, FileManager &file, WinnersCounter &winners, 
        LoosersCounter &loosers);
    ~ThAcceptor();
    void run();  
    ThClient accept_client(std::string num_to_guess, WinnersCounter &winners, 
        LoosersCounter &loosers);

private:
    std::vector<Thread*> threads;
    Socket &s;
    FileManager &file;
    WinnersCounter &winners;
    LoosersCounter &loosers;
};

#endif
