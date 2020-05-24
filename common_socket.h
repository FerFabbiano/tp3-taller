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
    
    /* Devuelvo un socket por movimiento. */
    Socket accept();
    
    void bind_and_listen(const char *service);
    
    void connect(const char *host_name, const char *service);
    
    int send(const char *buffer, size_t length) const;
    
    int receive(char *buffer, size_t buf_length) const;
    
    void set_hints(addrinfo *hints, int tipo);

    void close();
    
    Socket(const Socket& copy) = delete;
    Socket& operator=(const Socket &copy) = delete;
    
    Socket(Socket &&other) noexcept;
    Socket& operator=(Socket &&other);
};

#endif
