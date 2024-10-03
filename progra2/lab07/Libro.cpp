//
// Created by marcos on 6/12/24.
//

#include "Libro.hpp"
using namespace std;

bool Libro::isColocado() const {
    return colocado;
}

void Libro::setColocado(bool colocado) {
    Libro::colocado = colocado;
}

double Libro::getPeso() const {
    return peso;
}

void Libro::setPeso(double peso) {
    Libro::peso = peso;
}

int Libro::getAlto() const {
    return alto;
}

void Libro::setAlto(int alto) {
    Libro::alto = alto;
}

int Libro::getAncho() const {
    return ancho;
}

void Libro::setAncho(int ancho) {
    Libro::ancho = ancho;
}
void Libro::getNombre(char *n) const {
    if (nombre == nullptr) n[0] = 0;
    else strcpy (n, nombre);
}

void Libro::setNombre(const char *n) {
    if (codigo != nullptr) delete nombre;
    nombre = new char [strlen (n) + 1];
    strcpy (nombre, n);
}

void Libro::getCodigo(char *n) const {
    if (codigo == nullptr) n[0] = 0;
    else strcpy (n, codigo);}

void Libro::setCodigo(const char *n) {
    if (codigo != nullptr) delete codigo;
    codigo = new char [strlen (n) + 1];
    strcpy (codigo, n);
}

Libro::Libro() {
    codigo = nullptr;
    nombre = nullptr;
    ancho = 0;
    alto = 0;
    peso = 0;
    colocado = 0;
}

Libro::~Libro() {
    if (codigo != nullptr) delete codigo;
    if (nombre != nullptr) delete nombre;
}

