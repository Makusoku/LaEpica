//
// Created by marcos on 6/12/24.
//

#include "Enciclopedia.hpp"
using namespace std;

Enciclopedia::Enciclopedia() {
    peso = 0;
    volumen = 0;
}

Enciclopedia::~Enciclopedia() {
}

int Enciclopedia::getVolumen() const {
    return volumen;
}

void Enciclopedia::setVolumen(int volumen) {
    Enciclopedia::volumen = volumen;
}

double Enciclopedia::getPeso1() const {
    return peso;
}

void Enciclopedia::setPeso1(double peso) {
    Enciclopedia::peso = peso;
}

void Enciclopedia::leerEnciclopedias(std::ifstream &arch) {
    arch.get();
    arch >> ws;
    char codigo[10], descr[100], car;
    int anchura, altura, volumen_enciclopedia;
    double peso_enciclopedia;

    arch.getline(codigo, 10, ',');
    arch >> ws;
    arch.getline(descr, 100, ',');
    arch >> anchura >> car >> altura >> car >>
    volumen_enciclopedia >> car >> peso_enciclopedia >> ws;

    setCodigo(codigo);
    setNombre(descr);
    setAlto(altura);
    setAncho(anchura);
    setVolumen(volumen_enciclopedia);
    setPeso1(peso_enciclopedia);
    setPeso(peso_enciclopedia);
}

