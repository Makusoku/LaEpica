//
// Created by marcos on 6/12/24.
//

#include "EstanteHorizontal.hpp"
using namespace std;

EstanteHorizontal::EstanteHorizontal() {
    cantidad_novelas = 0;
}

EstanteHorizontal::~EstanteHorizontal() {
}

int EstanteHorizontal::getCantidadNovelas() const {
    return cantidad_novelas;
}

void EstanteHorizontal::setCantidadNovelas(int cantidadNovelas) {
    cantidad_novelas = cantidadNovelas;
}

