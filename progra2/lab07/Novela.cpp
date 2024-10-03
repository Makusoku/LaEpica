//
// Created by marcos on 6/12/24.
//

#include "Novela.hpp"
using namespace std;

Novela::Novela() {
    peso = 0;
    tipo = nullptr;
}

Novela::~Novela() {
    if (tipo != nullptr) delete tipo;
}

void Novela::getTipo(char *n) const {
    if (tipo == nullptr) n[0] = 0;
    else strcpy (n, tipo);
}

void Novela::setTipo(const char *n) {
    if (tipo != nullptr) delete tipo;
    tipo = new char [strlen (n) + 1];
    strcpy (tipo, n);
}

double Novela::getPeso1() const {
    return peso;
}

void Novela::setPeso1(double peso) {
    Novela::peso = peso;
}


void Novela::leerLibros(std::ifstream &arch) {
    arch.get();
    arch >> ws;
    char codigo[10], descr[100], tipo_novela[50], car;
    int anchura, altura;
    double peso_novela;

    arch.getline(codigo, 10, ',');
    arch >> ws;
    arch.getline(descr, 100, ',');
    arch >> anchura >> car >> altura >> car >> ws;
    arch.getline(tipo_novela, 50, ',');
    arch >> peso_novela >> ws;

    setCodigo(codigo);
    setNombre(descr);
    setAlto(altura);
    setAncho(anchura);
    setTipo(tipo_novela);
    setPeso1(peso_novela);
    setPeso(peso_novela);
}