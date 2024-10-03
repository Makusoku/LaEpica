//
// Created by marcos on 6/19/24.
//

#include "Lista.hpp"
using namespace std;

Lista::Lista() {
    ini = nullptr;
    peso = 0;
}

double Lista::getPeso() const {
    return peso;
}

void Lista::setPeso(double peso) {
    Lista::peso = peso;
}

void Lista::inserta_elemento(class Libro *nuevo) {
    peso += nuevo->getPeso();
    class Nodo *ptr = ini;
    class Nodo *nuevo_nodo;
    nuevo_nodo = new class Nodo;
    nuevo_nodo->plibro = nuevo;
    if (ptr == nullptr) ini = nuevo_nodo;
    else {
        while (ptr->sig != nullptr) ptr = ptr->sig;
        ptr->sig = nuevo_nodo;
    }
}

void Lista::imprime_lista(std::ofstream &arch) {
    Nodo *ptr = ini;
    while (ptr != nullptr) {
        ptr->plibro->imprime (arch);
        ptr = ptr->sig;
    }
}

void Lista::baja_vigencia_libro() {
    Nodo *ptr = ini;
    while (ptr != nullptr) {
        ptr->plibro->actualiza ();
        ptr = ptr->sig;
    }
}