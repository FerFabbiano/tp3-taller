#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <exception>      // std::exception
#include "common_SocketError.h"

#define SERVER 1
#define CLIENT 0

class Socket{
private: 
    int fd;
    explicit Socket(int fd); // solo podrá ser llamado por socket

public: 
    Socket();
    ~Socket();
    /* Acepto, y devuelvo un socket por movimiento. */
    Socket accept();
    void bind_and_listen(const char *service);
    void connect(const char *host_name, const char *service);
    /* Envío un buffer de tamaño length, y devuelvo la cantidad de bytes 
    enviados */
    int send(const char *buffer, size_t length) const;
    /* Recibo un buffer de tamaño length y devuelvo la cantidad de bytes
    recibidos */
    int receive(char *buffer, size_t buf_length) const;
    /* Seteo los atributos de addrinfo según tipo (1->Server, 0->Client) */
    void set_hints(addrinfo *hints, int tipo);
    /* Shutdown de los canales tanto de escritura como de lectura del socket */
    void close();
    Socket(const Socket& copy) = delete;
    Socket& operator=(const Socket &copy) = delete;
    Socket(Socket &&other) noexcept;
    Socket& operator=(Socket &&other);
};

#endif
