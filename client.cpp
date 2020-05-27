#include <iostream>
#include <string>

#include "common_client.h"
#include "common_socket.h"
#include "common_OSError.h"

int main(int argc, char const *argv[]){   
    std::string arg_invalido = "Error: argumentos invalidos.";
    try{
        if (argc != 3){
            throw OSError(arg_invalido);
        }
        Client client;
        client.connect(argv[1], argv[2]);
        client.init();
    }catch(std::exception &e){
        std::cout << e.what() << '\n';
        return 0;
    }
    return 0;
}
