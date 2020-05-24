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

    WinnersCounter winners;
    LoosersCounter loosers;

    Socket s;
    s.bind_and_listen(argv[1]);

    ThAcceptor acceptor(s, file, winners, loosers);
    acceptor.start();
    acceptor.join();

    /*
    std::string num_to_guess = file.get_number();
    try{
        file.valid_number(num_to_guess);
    }
    catch(OSError &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
*/

    winners.print_winners();
    loosers.print_loosers();

    return 0;
}
