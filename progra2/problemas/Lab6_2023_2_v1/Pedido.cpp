//
// Created by marcos on 5/22/24.
//

#include <iostream>
#include <cstring>
#include  <fstream>
#include "Pedido.hpp"
using namespace std;

Pedido::Pedido() {
    codigo = nullptr;
    dni_cliente = 0;
    precio_producto = 0;
}

int Pedido::getDniCliente() const {
    return dni_cliente;
}

void Pedido::setDniCliente(int dniCliente) {
    dni_cliente = dniCliente;
}

void Pedido::getCodigo(char *n) const {
    if (codigo == nullptr) n[0] = 0;
    else strcpy(n, codigo);
}

void Pedido::setCodigo(const char *n) {
    if (codigo != nullptr) delete codigo;
    codigo = new char [strlen (n) + 1]{};
    strcpy(codigo, n);
}

bool operator >> (ifstream &inArch, Pedido &p) {
    char *bufcod, buff[200];
    inArch.getline(buff, 200, ',');
    if (inArch.eof()) return false;
    bufcod = new char [strlen(buff) + 1]{};
    strcpy(bufcod, buff);
    int n; inArch >> n >> ws;
    p.setCodigo(bufcod);
    p.setDniCliente(n);
    return true;
}
