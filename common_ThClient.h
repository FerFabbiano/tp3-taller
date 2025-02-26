#ifndef THCLIENT_H
#define THCLIENT_H

#include <string>
#include <iostream>
#include "common_socket.h"
#include "common_socket.h"
#include "common_thread.h"
#include <atomic>
#include "common_stats.h"
#include "common_game.h"

class ThClient : public Thread{
public: 
    /* Constructor */
    ThClient(std::string num_to_guess, Socket socket, Game &game);
    /* Destructor */
    ~ThClient();
    /* Recibe el comando enviado a través del socket y un entero sin signo 
    de 2 bytes. Este entero será cero en caso de que el comando enviado
    no sea un número. Devuelvo la respuesta que debo enviar al cliente. */
    std::string set_answer(const char command, uint16_t number);
    /* Recibe por parámetro un string que contiene la respuesta que se le 
    debe enviar al cliente en base al comando recibido. Envío respuesta
    a través del socket. */
    void send_answer(std::string answer);
    /* Recibo los mensajes enviados por el cliente a través del socket, y
    los proceso para determinar que respuesta debe devolverle. Devuelvo
    la respuesta que debo enviarle al cliente. */
    std::string process_command();
    void run();
    /* Devuelvo falso si is_running es verdadero.
    Devuelvo verdadero caso contrario. */
    bool is_dead() const;
    ThClient(ThClient &&other) noexcept;
    ThClient& operator=(ThClient &&other);

private:
    std::string num_to_guess;
    Socket s;
    std::string help;
    std::string perdiste;
    std::string ganaste;
    std::atomic<bool> is_running;
    bool keep_reading;
    Game &game;
};


#endif
