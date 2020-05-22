#include <iostream>
#include <string>
#include <sstream>

#include "common_client.h"
#include "common_socket.h"
#include "common_OSError.h"

int main(int argc, char const *argv[]){   
    std::string arg_invalido = "Error: argumentos invalidos.";
    bool keep_reading = true;
    
    try{
        if (argc != 3){
            throw OSError(arg_invalido);
        }
    }
    catch(std::exception &e){
        std::cout << e.what() << '\n';
        return 0;
    }

    Socket s;
    s.connect(argv[1], argv[2]);

    Client client1(s);
    while (keep_reading){
        try{
            client1.read_stdin();
        }
        catch(std::exception &e){
            std::cout << e.what() << '\n';
        }
    }
  

    /*
    char buffer_send[5] = "OK!\n";
    char buffer_recv[5];
    Socket socket;
    socket.connect(argv[1], argv[2]);
    socket.send(buffer_send, sizeof(buffer_send));
    socket.receive(buffer_recv, sizeof(buffer_recv));
    std::cout << buffer_recv << std::endl;
    */
    return 0;
}
