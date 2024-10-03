//
// Created by marcos on 6/17/24.
//

#include "Biblioteca.hpp"
using namespace std;

Biblioteca::Biblioteca() {
    cantidad_estantes = 0;
    cantidad_libros = 0;
}

Biblioteca::~Biblioteca() {

}

int Biblioteca::getCantidadEstantes() const {
    return cantidad_estantes;
}

void Biblioteca::setCantidadEstantes(int cantidadEstantes) {
    cantidad_estantes = cantidadEstantes;
}

int Biblioteca::getCantidadLibros() const {
    return cantidad_libros;
}

void Biblioteca::setCantidadLibros(int cantidadLibros) {
    cantidad_libros = cantidadLibros;
}
