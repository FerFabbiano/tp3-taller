#include <iostream>
#include <vector>
#include <string>

#include "common_socket.h"
#include "common_ThClient.h"
#include "common_fileManager.h"
#include "common_OSError.h"
#include "common_ThAcceptor.h"
#include "common_winnersCounter.h"
#include "common_loosersCounter.h"
#include "common_impresor.h"

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
    WinnersCounter winners;
    LoosersCounter loosers;
    std::string quit;
    bool wait = true;
    Socket s;
    try{
        s.bind_and_listen(argv[1]);
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    ThAcceptor acceptor(s, file, winners, loosers);
    acceptor.start();
    while (wait){
        std::getline(std::cin, quit);
        if (quit.compare("q") == 0){
            wait = false;
            s.close(); 
            acceptor.stop_accepting();
        }
    }
    acceptor.join();
    
    Impresor impresor;
    impresor(winners.get_winners(), loosers.get_loosers());

    return SUCCESS;
}
