#include "common_fileManager.h"
#include "common_OSError.h"
#include <string>

FileManager::FileManager(const char* filename) : filename(filename){
    fs.open(this->filename);
    if (!fs.is_open())
        throw OSError("Error al abrir el archivo.");
    counter = 0;
}

FileManager::~FileManager(){
    if (fs.is_open()){
        fs.close();
    }
}

std::string FileManager::get_number(){
    std::string number;
    if (counter == (unsigned int) numbers.size()){
        counter = 0;
    }
    number = numbers.at(counter);
    counter++;
    return number;
}

void FileManager::valid_number(std::string number){
    if (std::stoi(number) > 1000){
        throw OSError("Error: archivo con números fuera de rango");
    }else if ((number[0] == number [1]) || (number[0] == number[2]) || 
        (number[1] == number[2])){
        throw OSError("Error: formato de los números inválidos");
    }
}

void FileManager::valid_file(){
    std::string number;
    while (!fs.eof()){
        getline(fs, number);
        numbers.push_back(number);
        counter ++;
        valid_number(number);
    }
}
