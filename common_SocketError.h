#include <typeinfo>
#include <string>

class SocketError : public std::exception {
private:
    std::string mssg_error;
public:
    explicit SocketError(const std::string &error) noexcept;
    virtual const char *what() const noexcept;
    virtual ~SocketError() noexcept;   
};
