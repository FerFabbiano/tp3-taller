#include <errno.h>
#include <iostream>
#include <string>

#include "common_SocketError.h"

SocketError::SocketError(const std::string &error) noexcept {
    this->mssg_error = error;
}

const char* SocketError::what() const noexcept{
    return this->mssg_error.c_str();
}

SocketError::~SocketError() {}
