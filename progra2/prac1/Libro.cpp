//
// Created by marcos on 6/17/24.
//

#include "Libro.hpp"
using namespace std;

Libro::Libro() {
    codigo = nullptr;
    nombre = nullptr;
    ancho = 0;
    alto = 0;
    colocado = false;
}

Libro::~Libro() {
    if (codigo != nullptr) delete codigo;
    if (nombre != nullptr) delete nombre;
}

void Libro::getCodigo(char *n) const {
    if (codigo == nullptr) n[0] = 0;
    else strcpy (n, codigo);
}

void Libro::setCodigo(const char *n) {
    if (codigo != nullptr) delete codigo;
    codigo = new char [strlen (n) + 1]{};
    strcpy(codigo, n);
}

void Libro::getNombre(char *n) const {
    if (nombre == nullptr) n[0] = 0;
    else strcpy (n, nombre);
}

void Libro::setNombre(const char *n) {
    if (nombre != nullptr) delete nombre;
    nombre = new char [strlen (n) + 1]{};
    strcpy(nombre, n);
}

int Libro::getAncho() const {
    return ancho;
}

void Libro::setAncho(int ancho) {
    Libro::ancho = ancho;
}

int Libro::getAlto() const {
    return alto;
}

void Libro::setAlto(int alto) {
    Libro::alto = alto;
}

bool Libro::isColocado() const {
    return colocado;
}

void Libro::setColocado(bool colocado) {
    Libro::colocado = colocado;
}

void Libro::leer_libro(std::ifstream &arch) {
    char cod[200], nom[200], car;
    arch.getline(cod, 200, ',');
    arch.getline(nom, 200, ',');
    arch >> ancho >> car >> alto >> ws;
    setCodigo(cod);
    setNombre(nom);
}

void operator >> (std::ifstream &arch, Libro &libros) {
    libros.leer_libro(arch);
}

void Libro::copiar(Libro &libro) {
    alto = libro.getAlto();
    ancho = libro.getAncho();
    char nom[200], cod[200];
    libro.getCodigo(cod);
    libro.getNombre(nom);
    setCodigo(cod);
    setNombre(nom);
}