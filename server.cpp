#include <iostream>
#include "common_socket.h"
#include "common_ThClient.h"
#include "common_fileManager.h"
#include "common_OSError.h"
#include "common_ThAcceptor.h"
#include <vector>

int main(int argc, char const *argv[]){
    try{
        if (argc != 3)
            throw OSError("Error: argumentos invalidos.");
    }catch(OSError &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    FileManager file(argv[2]);
    Socket s;
    s.bind_and_listen(argv[1]);

    ThAcceptor acceptor(s, file);
    acceptor.start();
    acceptor.join();

    /*
    std::string num_to_guess = file.get_number();
    try{
        file.valid_number(num_to_guess);
    }
    catch(OSError &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    //std::vector<Thread*> threads;

    //int j = 0;
    //bool is_running = true;

    Socket s;
    s.bind_and_listen(argv[1]);
    Socket socket_accept = s.accept();
        for(int i=0; i < 1; i++){
        threads.push_back(new ThClient(num_to_guess, socket_accept));
        threads[i]->start();   
    }
    std::cout << (int)threads.size() << std::endl;
  
    Socket socket_accept = s.accept();
    threads.push_back(new ThClient(num_to_guess, socket_accept));
    threads[j]->start();   
    j++;
    Socket socket_accept2 = s.accept();
    threads.push_back(new ThClient(num_to_guess, socket_accept2));
    threads[j]->start();   
    j++;
    Socket socket_accept3 = s.accept();
    threads.push_back(new ThClient(num_to_guess, socket_accept3));
    threads[j]->start();   
    j++;
    std::cout << (int)threads.size() << std::endl;

    for (int i = 0; i < (int)threads.size(); i++){
        threads[i]->join();    
        delete(threads[i]);
    }
*/

    return 0;
}
