#include "common_impresor.h"

void Impresor::operator()(int winners, int loosers){
    std::cout << "Estadísticas:\n      Ganadores:  " << winners << '\n'
    << "      Perdedores: " << loosers << '\n';
}
