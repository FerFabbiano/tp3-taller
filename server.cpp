#include <iostream>
#include "common_socket.h"
#include "common_ThClient.h"
#include "common_fileManager.h"
#include "common_OSError.h"

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
    uint16_t numero = 748;
    //client1.set_answer("h", numero);
    //client1.set_answer("s", numero); 
    client1.set_answer("n", numero);
    
    /*
    char recv_num[2];
    char recv_command[1];
    memset (recv_command, 0, 1);
    bool keep_recv  = true;
    Socket s;
    s.bind_and_listen(argv[1]);
    Socket socket_accept = s.accept();
    while (keep_recv){
        socket_accept.receive(recv_command, 1);
        std::cout << recv_command[0] << std::endl;
        if (strchr(recv_command, 'n') != nullptr){
            socket_accept.receive(recv_num, sizeof(recv_num));
            uint16_t numero = *(uint16_t*) recv_num;
            std::cout << numero << std::endl;
        }
    }
    */
    return 0;
}
