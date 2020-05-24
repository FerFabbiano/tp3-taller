#ifndef THACCEPTOR_H
#define THACCEPTOR_H

#include "common_thread.h"
#include <vector>
#include "common_socket.h"
#include "common_fileManager.h"

class ThAcceptor : public Thread{
public:
    ThAcceptor(Socket &s, FileManager &file);
    ~ThAcceptor();
    void run();  

private:
    std::vector<Thread*> threads;
    Socket &s;
    FileManager &file;
};

#endif