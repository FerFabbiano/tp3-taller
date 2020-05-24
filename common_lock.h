#ifndef LOCK_H
#define LOCK_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class Lock {
private:
    std::mutex &m;
public:
    explicit Lock(std::mutex &m);
    ~Lock();
private:
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
    Lock(Lock&&) = delete;
    Lock& operator=(Lock&&) = delete;
};

#endif
