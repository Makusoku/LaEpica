//
// Created by marcos on 6/14/24.
//

#include "Promociones.hpp"
using namespace std;

Promociones::Promociones() {

}

Promociones::~Promociones() {

}

void Promociones::leepedidos() {
    ifstream arch ("pedidos5.csv", ios :: in);
    if (!arch.is_open()) {
        cout << "Error al abrir pedidos5.csv" << endl;
        exit (1);
    }

    int codigo;

    while (1) {
        arch >> codigo;
        if (arch.eof()) break;
        arch.get();
        Lpedidos.lee_inserta (arch, codigo);
    }
}

void Promociones::imprimepedidos() {
    Lpedidos.muestra ();
}