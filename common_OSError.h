#include <typeinfo>
#include <string>

class OSError : public std::exception {
private:
    std::string mssg_error;
public:
    explicit OSError(const std::string &error) noexcept;
    virtual const char *what() const noexcept;
    virtual ~OSError() noexcept;   
};
