#include <string>
#include "common_socket.h"
#include "common_protocol.h"

class Client{
private: 
    Socket s;
    char command_send;
    bool continue_playing;    
    uint16_t number_send;
    Protocol protocol;
    
public: 
    /* Constructor */
    Client();
    void init();
    /* Leo el comando ingresado por el cliente el la entrada estándar. 
    Devuelvo el comando en un string. */
    std::string read_stdin();
    /* Envío el comando ingresado por el cliente, formateado, a través del 
    socket. En caso de haber ingresado un número, envío el comando y 
    luego envío dicho número. */
    void send_command(std::string command);
    /* Recibo la respuesta proveniente del servidor en base al comando y/o número
    enviado. */
    std::string receive();
    /* Recibo por parámetro un string. Devuelvo verdadero si no coincide con
    "ganaste" o "perdiste". Falso caso contrario. */
    bool check_answer(std::string answer);
    /* Destructor */
    void connect(const char *host_name, const char *service);
    ~Client();
};
