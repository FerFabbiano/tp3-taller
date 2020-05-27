#include <iostream>
#include <string>

#include "common_OSError.h"

OSError::OSError(const std::string &error) noexcept : mssg_error(error){}

const char* OSError::what() const noexcept{
    return this->mssg_error.c_str();
}

OSError::~OSError() {}
