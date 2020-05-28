#include "common_impresor.h"

void Impresor::operator()(int winners, int losers){
    std::cout << "Estadísticas:\n\tGanadores:  " << winners << '\n'
    << "\tPerdedores: " << losers << '\n';
}
