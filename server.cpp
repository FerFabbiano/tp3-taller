#include <iostream>
#include <vector>
#include <string>

#include "common_socket.h"
#include "common_ThClient.h"
#include "common_fileManager.h"
#include "common_OSError.h"
#include "common_ThAcceptor.h"
#include "common_playersCounter.h"
#include "common_loosersCounter.h"
#include "common_impresor.h"
#include <vector>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char const *argv[]){
    try{
        if (argc != 3)
            throw OSError("Error: argumentos invalidos.");
    }catch(OSError &e){
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    FileManager file(argv[2]);
    try{
        file.valid_file();
    }catch(OSError &e){
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    PlayersCounter winners;
    PlayersCounter loosers;
    std::string quit;
    bool wait = true;
    ThAcceptor acceptor(file, winners, loosers);
    acceptor.init(argv[1]);
    acceptor.start();
    while (wait){
        std::cin >> quit;
        if (quit.compare("q") == 0){
            wait = false;
            acceptor.stop_accepting();
        }
    }
    acceptor.join();
    
    Impresor impresor;
    impresor(winners.get_counter(), loosers.get_counter());

    return SUCCESS;
}
