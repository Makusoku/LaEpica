//
// Created by marcos on 6/12/24.
//

#include "Espacio.hpp"
using namespace std;

Espacio::Espacio() {
    contenido = ' ';
    posx = 0;
    posy = 0;
}

Espacio::~Espacio() {

}

char Espacio::getContenido() const {
    return contenido;
}

void Espacio::setContenido(char contenido) {
    Espacio::contenido = contenido;
}

int Espacio::getPosx() const {
    return posx;
}

void Espacio::setPosx(int posx) {
    Espacio::posx = posx;
}

int Espacio::getPosy() const {
    return posy;
}

void Espacio::setPosy(int posy) {
    Espacio::posy = posy;
}
