//
// Created by marcos on 6/19/24.
//

#include "Novela.hpp"
using namespace std;

Novela::Novela() {
    autor = nullptr;
}

Novela::~Novela() {
    if (autor != nullptr) delete autor;
}

void Novela::getAutor(char *n) const {
    if(autor == nullptr) n[0] = 0;
    else strcpy(n, autor);
}

void Novela::setAutor(const char *n) {
    if (autor != nullptr) delete autor;
    autor = new char [strlen (n) + 1]{};
    strcpy(autor, n);
}

void Novela::lee(std::ifstream &arch) {
    Libro::lee(arch);
    char nom[200];
    arch.getline(nom, 200, '\r');
    setAutor(nom);
}

void Novela::imprime(std::ofstream &arch) {
    Libro::imprime(arch);
    char n[200];
    getAutor(n);
    arch << "Autor: " << n << endl << endl;
}

void Novela::actualiza() {

}