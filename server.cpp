#include <iostream>
#include "common_socket.h"

int main(int argc, char const *argv[]){
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
    
    return 0;
}
