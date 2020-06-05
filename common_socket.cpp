#include "common_socket.h"
#include <cerrno>
#include <utility>
#include "common_socketErrorIgnore.h"
#include "common_SocketError.h"

#define SERVEROUT 22

Socket::Socket() : fd(-1) {}

Socket::~Socket(){
    /* Si es válido, lo cierro. */
    if (this->fd != -1){
      ::close(this->fd);
    }
    /* Dejo el file descriptor en un estado inválido. */
    this->fd = -1;
}

Socket::Socket(Socket &&other) noexcept: fd(other.fd){
    /* Debo dejar a other en un estado inválido para que no me haga el close. */
    other.fd = -1;
}

Socket::Socket(int fd) : fd(fd) {}

Socket Socket::accept(){
    int fd = ::accept(this->fd, nullptr, nullptr);
    if (fd == -1){    
        if (errno == 22)
            throw SocketErrorIgnore();
        throw SocketError("Error en la función accept de Socket.");
    }
    return std::move(Socket(fd)); // devuelvo socket por movimiento
}

void Socket::bind_and_listen(const char *service){
    int status = 0, val = 1;
    struct addrinfo hints, *results, *aux;
    set_hints(&hints, SERVER);
    status = getaddrinfo(nullptr, service, &hints, &results);
    if (status != 0)
      throw SocketError("Error al intentar obtener lista de direcciones.");
    for (aux = results; aux != nullptr; aux = aux->ai_next) {
        this->fd = ::socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        if (this->fd == -1)
            continue;
        status = setsockopt(this->fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
        if (status == -1){
            ::close(this->fd);
            this->fd = -1;
        }
        if (bind(this->fd, aux->ai_addr, aux->ai_addrlen) == 0){
            break;               
        }
        ::close(this->fd);
        this->fd = -1;
    }
    if (this->fd == -1)
        throw SocketError("Error al intentar bindear el socket.");
    freeaddrinfo(results); /* libero lista de direcciones. */
    status = listen(this->fd, 10);
    if (status == -1)
        throw SocketError("Error en la función de socket listen.");
}

void Socket::set_hints(addrinfo *hints, int tipo){
    hints->ai_family = AF_INET;    
    hints->ai_socktype = SOCK_STREAM; 
    hints->ai_protocol = 0;
    if (tipo == SERVER){
        hints->ai_flags = AI_PASSIVE;
    }else{
        hints->ai_flags = 0;
    }
}

void Socket::connect(const char *host_name, const char *service){
    int status = 0;
    struct addrinfo hints, *results, *aux;
    set_hints(&hints, CLIENT);
    status = getaddrinfo(host_name, service, &hints, &results);
    if (status != 0)
        throw SocketError("Error en el connect del socket.");
    for (aux = results; aux != nullptr; aux = aux->ai_next) {
        this->fd = ::socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        if (this->fd == -1)
            continue;
        if (::connect(this->fd, aux->ai_addr, aux->ai_addrlen) == 0)
            break;               
        ::close(this->fd);
        this->fd = -1;
    }
    if (this->fd == -1)
        throw SocketError("Error al intentar conectar el socket.");
    freeaddrinfo(results); /* libero lista de direcciones. */
}

int Socket::send(const char *buffer, size_t buf_length) const{
    size_t size_send = 0, aux;
    while (size_send < buf_length){
        aux = ::send(this->fd, &buffer[size_send], buf_length - size_send, 
        MSG_NOSIGNAL);
        if (aux < 0)
            throw SocketError("Error al enviar mensaje por el socket.");
        size_send += aux;
    }
    return size_send;
}
    
int Socket::receive(char *buffer, size_t buf_length) const{
    size_t size_recv = 0, aux = 0;
    while (size_recv < buf_length){
        aux = ::recv(this->fd, &buffer[size_recv], buf_length - size_recv, 0);
        if (aux < 0)
            throw SocketError("Error al recibir mensaje por el socket.");
        size_recv += aux;
    }
    return size_recv;
}

void Socket::close(){
    ::close(this->fd);
}

void Socket::shutdown(){
    ::shutdown(this->fd, SHUT_RDWR);
}
