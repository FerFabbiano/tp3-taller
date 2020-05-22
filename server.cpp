#include <iostream>
#include "common_socket.h"

int main(int argc, char const *argv[]){
    char recv_num[2];
    char recv_command[1];
    bool keep_recv  = true;
    Socket socket;
    socket.bind_and_listen(argv[1]);
    Socket socket_accept = socket.accept();
    while(keep_recv){
        socket_accept.receive(recv_command, sizeof(recv_command));
        std::cout << recv_command << std::endl;
        if (strchr(recv_command, 'n') != nullptr){
            socket_accept.receive(recv_num, sizeof(recv_num));
            uint16_t numero = *(uint16_t*) recv_num;
            std::cout << numero << std::endl;
        }
    }
    
    return 0;
}
