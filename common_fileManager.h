#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <fstream>
#include <iostream>

class FileManager{
public:
    FileManager(const char* filename);
    ~FileManager();
    std::string get_number();
    void valid_number(std::string number);
private:
    std::string filename;
    std::ifstream fs;

};

#endif