#include <iostream>
#include <vector>
#include <string>

#include "common_socket.h"
#include "common_ThClient.h"
#include "common_fileManager.h"
#include "common_OSError.h"
#include "common_ThAcceptor.h"
#include "common_stats.h"
#include <vector>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char const *argv[]){
    try{
        if (argc != 3)
            throw OSError("Error: argumentos invalidos.");
        FileManager file(argv[2]);
        file.valid_file();
        Stats winners;
        Stats losers;
        std::string stop_accepting;
        bool should_wait = true;
        ThAcceptor acceptor(file, winners, losers);
        acceptor.init(argv[1]);
        acceptor.start();
        while (should_wait){
            std::cin >> stop_accepting;
            if (stop_accepting.compare("q") == 0){
                should_wait = false;
                acceptor.stop_accepting();
            }
        }
        acceptor.join();
        winners(winners.get_counter(), losers.get_counter());
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    return SUCCESS;
}
