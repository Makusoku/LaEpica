//
// Created by marcos on 6/12/24.
//

#include "EstanteVertical.hpp"
using namespace std;

EstanteVertical::EstanteVertical() {
    cantidad_enciclopedias = 0;
}

EstanteVertical::~EstanteVertical() {
}

int EstanteVertical::getCantidadEnciclopedias() const {
    return cantidad_enciclopedias;
}

void EstanteVertical::setCantidadEnciclopedias(int cantidadEnciclopedias) {
    cantidad_enciclopedias = cantidadEnciclopedias;
}

