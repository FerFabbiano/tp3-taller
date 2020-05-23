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
        
    bool keep_reading = true;
    
    Socket s;
    s.bind_and_listen(argv[1]);
    Socket socket_accept = s.accept();
    ThClient client1(num_to_guess, socket_accept);

    while (keep_reading){
        std::string answer = client1.process_command();
        client1.send_answer(answer);
        if ((answer.compare("Ganaste") == 0) || (answer.compare("Perdiste") == 0))
            keep_reading = false;
    }

    return 0;
}
