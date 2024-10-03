//
// Created by marcos on 6/12/24.
//

#include "Estante.hpp"
using namespace std;

Estante::Estante() {
    codigo = nullptr;
    anchura = 0;
    altura = 0;
    pesoSoportado = 0;
    pesoActual = 0;
}

Estante::~Estante() {
    if (codigo != nullptr) delete codigo;
}

void Estante::getCodigo(char * n) const {
    if (codigo == nullptr) n[0] = 0;
    else strcpy (n, codigo);
}

void Estante::setCodigo(const char *n) {
    if (codigo != nullptr) delete codigo;
    codigo = new char [strlen (n) + 1];
    strcpy (codigo, n);
}

int Estante::getAnchura() const {
    return anchura;
}

void Estante::setAnchura(int anchura) {
    Estante::anchura = anchura;
}

int Estante::getAltura() const {
    return altura;
}

void Estante::setAltura(int altura) {
    Estante::altura = altura;
}

double Estante::getPesoSoportado() const {
    return pesoSoportado;
}

void Estante::setPesoSoportado(double pesoSoportado) {
    Estante::pesoSoportado = pesoSoportado;
}

double Estante::getPesoActual() const {
    return pesoActual;
}

void Estante::setPesoActual(double pesoActual) {
    Estante::pesoActual = pesoActual;
}

void Estante::leerEstante(std::ifstream &arch) {
    char car, cod [10];
    int anch, alt;
    double peso_maximo;
    arch >> car >> ws;
    arch.getline(cod, 10, ',');
    arch >> anch >> car >> alt >> car >> peso_maximo >> ws;
    setCodigo(cod);
    setAltura(alt);
    setAnchura(anch);
    setPesoSoportado(peso_maximo);
}