//
// Created by marcos on 6/14/24.
//

#include "Lista.hpp"
#include "PedidoEspecial.hpp"
#include "PedidoEventual.hpp"
#include "PedidoUsual.hpp"
using namespace std;

Lista::Lista() {
    lini = nullptr;
    lfin = nullptr;
}

void Lista::lee_inserta(std::ifstream &arch, int codigo) {
    Pedido *nuevo;
    if (codigo < 400000) {
        nuevo = new class PedidoEspecial;
    }
    else if (codigo < 600000) {
        nuevo = new class PedidoUsual;
    }
    else {
        nuevo = new class PedidoEventual;
    }
    nuevo->lee(arch);
    nuevo->setCodigo(codigo);
    insertar (nuevo);
}

void Lista::insertar(Pedido *p) {
    class Nodo *nuevo, *actual, *ant = nullptr;
    nuevo = new class Nodo;
    nuevo->ped = p;
    actual = lini;
    while (actual) {
        if (!actual->ped->Pedido::cmp (nuevo->ped))
        ant = actual;
        actual = actual->sig;
    }
    if (lini == nullptr) lini = nuevo;
    else ant->sig = nuevo;

    lfin = nuevo;
}

void Lista::muestra() {
    Nodo *actual = lini;
    while (actual) {
        actual->ped->imprime();
        actual->ped->Pedido::imprime();
        actual = actual->sig;
    }
}