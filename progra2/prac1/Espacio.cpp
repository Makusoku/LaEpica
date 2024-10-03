//
// Created by marcos on 6/17/24.
//

#include "Espacio.hpp"
using namespace std;

Espacio::Espacio() {
    contenido = ' ';
    posy = 0;
    posx = 0;
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

void operator << (ofstream &arch, Espacio &espacio) {
    arch << "[" << espacio.getContenido() << "]";
}