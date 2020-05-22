#include <iostream>
#include "common_socket.h"

int main(int argc, char const *argv[]){
    char buffer_recv[2];
    Socket socket;
    socket.bind_and_listen(argv[1]);
    Socket socket_accept = socket.accept();
    socket_accept.receive(buffer_recv, sizeof(buffer_recv));
    uint16_t numero = *(uint16_t*) buffer_recv;
    std::cout << numero << std::endl;
    
    /*
    socket_accept.receive(buffer_recv, sizeof(buffer_recv));
    std::cout << buffer_recv << std::endl;
    socket_accept.receive(buffer_recv, sizeof(buffer_recv));
    std::cout << buffer_recv << std::endl;
    */
    return 0;
}
