#include <iostream>
#include <vector>

#include "common_socket.h"
#include "common_ThClient.h"
#include "common_fileManager.h"
#include "common_OSError.h"
#include "common_ThAcceptor.h"
#include "common_winnersCounter.h"
#include "common_loosersCounter.h"

int main(int argc, char const *argv[]){
    try{
        if (argc != 3)
            throw OSError("Error: argumentos invalidos.");
    }catch(OSError &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    FileManager file(argv[2]);
    try{
        file.valid_file();
    }catch(OSError &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    WinnersCounter winners;
    LoosersCounter loosers;
    std::string quit;
    bool wait = true;

    Socket s;
    s.bind_and_listen(argv[1]);

    ThAcceptor acceptor(s, file, winners, loosers);
    acceptor.start();
    while(wait){
        std::getline(std::cin, quit);
        if (quit.compare("q") == 0){
            wait = false;
            s.close(); 
            acceptor.stop_accepting();
        }
    }
    acceptor.join();

    std::cout << "Estadísticas:\n";
    winners.print_winners();
    loosers.print_loosers();

    return 0;
}
