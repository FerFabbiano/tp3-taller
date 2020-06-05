#ifndef SOCKET_ERROR_IGNORE
#define SOCKET_ERROR_IGNORE

#include <typeinfo>
#include <string>

class SocketErrorIgnore : public std::exception {
public:
    SocketErrorIgnore();
    virtual~SocketErrorIgnore() noexcept;   
};

#endif
