#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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
    /* Válido los números que contiene el archivo. Si alguno de ellos no es 
    considerado válido, lanzo una excepción y finalizo el programa
    con códifo de retorno 1 */
    void valid_file();
private:
    std::string filename;
    std::ifstream fs;
    std::vector<std::string> numbers;
    unsigned int counter;
};

#endif
