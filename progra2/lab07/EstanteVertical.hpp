//
// Created by marcos on 6/12/24.
//

#ifndef LAB07_ESTANTEVERTICAL_HPP
#define LAB07_ESTANTEVERTICAL_HPP

#include "Estante.hpp"
#include "Enciclopedia.hpp"
using namespace std;

class EstanteVertical : public Estante {
private:
    Enciclopedia enciclopedias[50];
    int cantidad_enciclopedias;

public:
    EstanteVertical();

    ~EstanteVertical();

    int getCantidadEnciclopedias() const;

    void setCantidadEnciclopedias(int cantidadEnciclopedias);
};


#endif //LAB07_ESTANTEVERTICAL_HPP
