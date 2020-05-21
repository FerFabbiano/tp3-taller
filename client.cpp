#include <iostream>
#include <string>
#include <sstream>

#include "common_ThClient.h"
#include "common_socket.h"

int main (int argc, char const *argv[])
{   
    /*
    ThClient client1;
    client1.read_stdin();
    */
    char buffer_send[5] = "OK!\n";
    char buffer_recv[5];
    Socket socket;
    socket.connect(argv[1], argv[2]);
    socket.send(buffer_send, sizeof(buffer_send));
    socket.receive(buffer_recv, sizeof(buffer_recv));
    std::cout << buffer_recv << std::endl;

    return 0;

}
