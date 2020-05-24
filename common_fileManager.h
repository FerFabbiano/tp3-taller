#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <fstream>
#include <iostream>

class FileManager{
public:
    explicit FileManager(const char* filename);
    ~FileManager();
    /* Obtengo un número del archivo de entrada para utilizarlo en el juego. */
    std::string get_number();
    /* Chequeo si el número obtenido del archivo es vaĺido para utilizar
    en el juego. Caso negativo, lanzo una excepción que deberá terminar
    el juego, y devolver 1. */
    void valid_number(std::string number);
private:
    std::string filename;
    std::ifstream fs;
};

#endif
