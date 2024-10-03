//
// Created by marcos on 6/19/24.
//

#include "Libro.hpp"
using namespace std;

Libro::Libro() {
    nombre = nullptr;
    peso = 0;
    paginas = 0;
}

Libro::~Libro() {
    if (nombre != nullptr) delete nombre;
}

void Libro::getNombre(char *n) const {
    if(nombre == nullptr) n[0] = 0;
    else strcpy(n, nombre);
}

void Libro::setNombre(const char *n) {
    if (nombre != nullptr) delete nombre;
    nombre = new char [strlen (n) + 1]{};
    strcpy(nombre, n);
}

int Libro::getPaginas() const {
    return paginas;
}

void Libro::setPaginas(int paginas) {
    Libro::paginas = paginas;
}

double Libro::getPeso() const {
    return peso;
}

void Libro::setPeso(double peso) {
    Libro::peso = peso;
}

void Libro::lee(std::ifstream &arch) {
    arch.get();
    arch >> ws;
    char nom[200], car;
    arch.getline(nom, 200 , ',');
    arch >> paginas >> car >> peso >> car;
    setNombre(nom);
}

void Libro::imprime(std::ofstream &arch) {
    char n[200];
    getNombre(n);
    arch << "Titulo: " << n << endl;
    arch << "Peso: " << peso << endl;
}