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
    try{
        s.connect(argv[1], argv[2]);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    Client client1(s);
    while (keep_reading){
        std::string command = client1.read_stdin();
        std::string answer;
        try{
            client1.send_command(command);
            answer = client1.rcv_answer();
        }
        catch(std::exception &e){
            std::cout << e.what() << '\n';
        }
        keep_reading = client1.check_answer(answer);
    }
    return 0;
}
