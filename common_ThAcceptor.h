#ifndef THACCEPTOR_H
#define THACCEPTOR_H

#include "common_thread.h"
#include <vector>
#include "common_socket.h"
#include "common_fileManager.h"
#include <string>
#include "common_ThClient.h"
#include "common_loosersCounter.h"
#include "common_winnersCounter.h"

class ThAcceptor : public Thread{
public:
    /* Constructor */
    ThAcceptor(Socket &s, FileManager &file, WinnersCounter &winners, 
        LoosersCounter &loosers);
    /* Destructor */
    ~ThAcceptor();
    void run();  
    /* Acepto un nuevo cliente, y devuelvo un ThClient por movimiento */
    ThClient accept_client(std::string num_to_guess, WinnersCounter &winners, 
        LoosersCounter &loosers);
    /* Seteo keep_accepting y push en falso, para que el hilo sepa que no
    debe aceptar nuevos clientes. */
    void stop_accepting();
    /* Borro los clientes que ya finalizaron de la lista de clientes. 
    Evito leaks, hago de garbagge collector. */
    void delete_finish_clients(std::vector<ThClient*> &threads);

private:
    std::vector<ThClient*> threads;
    Socket &s;
    FileManager &file;
    WinnersCounter &winners;
    LoosersCounter &loosers;
    std::atomic<bool> keep_accepting;
};

#endif
