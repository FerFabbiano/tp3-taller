#include <iostream>
#include "common_socket.h"

int main(int argc, char const *argv[]){
    char buffer_recv[5];
    char buffer_send[5] = "OK!\n";
    Socket socket;
    socket.bind_and_listen(argv[1]);
    Socket socket_accept = socket.accept();
    socket_accept.receive(buffer_recv, sizeof(buffer_recv));
    std::cout << buffer_recv << std::endl;
    socket_accept.send(buffer_send, sizeof(buffer_send));
    return 0;
}