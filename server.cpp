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
        FileManager file(argv[2]);
        file.valid_file();
        PlayersCounter winners;
        PlayersCounter loosers;
        std::string stop;
        bool should_wait = true;
        ThAcceptor acceptor(file, winners, loosers);
        acceptor.init(argv[1]);
        acceptor.start();
        while (should_wait){
            std::cin >> stop;
            if (stop.compare("q") == 0){
                should_wait = false;
                acceptor.stop_accepting();
            }
        }
        acceptor.join();
        Impresor impresor;
        impresor(winners.get_counter(), loosers.get_counter());
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    return SUCCESS;
}
