#include "common_impresor.h"

void Impresor::operator()(int winners, int loosers){
    std::cout << "Estadísticas:\n\tGanadores:  " << winners << '\n'
    << "\tPerdedores: " << loosers << '\n';
}
