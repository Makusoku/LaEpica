//
// Created by marcos on 6/12/24.
//

#ifndef LAB07_ESTANTEHORIZONTAL_HPP
#define LAB07_ESTANTEHORIZONTAL_HPP

#include "Estante.hpp"
#include "Novela.hpp"
using namespace std;


class EstanteHorizontal : public Estante {
private:
    Novela novelas[50];
    int cantidad_novelas;

public:
    EstanteHorizontal();
    ~EstanteHorizontal();

    int getCantidadNovelas() const;

    void setCantidadNovelas(int cantidadNovelas);

};


#endif //LAB07_ESTANTEHORIZONTAL_HPP
