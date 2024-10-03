//
// Created by marcos on 6/17/24.
//

#ifndef PRAC1_ESPACIO_HPP
#define PRAC1_ESPACIO_HPP

#include "utils.hpp"
using namespace std;

class Espacio {
private:
    char contenido;
    int posx;
    int posy;

public:
    Espacio();

    virtual ~Espacio();

    char getContenido() const;

    void setContenido(char contenido);

    int getPosx() const;

    void setPosx(int posx);

    int getPosy() const;

    void setPosy(int posy);


};

void operator << (ofstream &arhc, Espacio &espacio);

#endif //PRAC1_ESPACIO_HPP
