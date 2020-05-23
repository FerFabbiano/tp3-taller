#include <iostream>
#include "common_socket.h"
#include "common_ThClient.h"
#include "common_fileManager.h"
#include "common_OSError.h"

#define INVALID -1

int main(int argc, char const *argv[]){
    try{
        if (argc != 3)
            throw OSError("Error: argumentos invalidos.");
    }catch(OSError &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    FileManager file(argv[2]);
    std::string num_to_guess = file.get_number();
    try{
        file.valid_number(num_to_guess);
    }
    catch(OSError &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    ThClient client1(num_to_guess);
    //uint16_t numero = 749;
    //client1.set_answer("h", numero);
    //client1.set_answer("s", numero); 
    //client1.set_answer("n", numero);
    
    char recv_num[2];
    char recv_command[2];
    uint16_t numero = INVALID;
    bool keep_recv  = true;
    Socket s;
    s.bind_and_listen(argv[1]);
    Socket socket_accept = s.accept();
    while (keep_recv){
        socket_accept.receive(recv_command, 1);
        if (*recv_command == 'n'){
            socket_accept.receive(recv_num, 2);
            numero = *(uint16_t*) recv_num;
        }
        client1.set_answer(recv_command, numero);
        numero = INVALID;
    }
    return 0;
}
