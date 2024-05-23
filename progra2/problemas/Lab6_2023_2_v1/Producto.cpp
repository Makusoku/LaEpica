//
// Created by marcos on 5/22/24.
//
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#include "Producto.hpp"

Producto::Producto() {
    codigo = nullptr;
    descripcion = nullptr;
    precio = 0;
    stock = 0;
    for (auto &it : clientes_servidos) it = 0;
    for (auto &it : clientes_no_servidos) it = 0;
    cantidad_clientes_servidos = 0;
    cantidad_clientes_no_servidos = 0;
}

Producto::~Producto(){
}

void Producto::getCodigo(char *n) const {
    if (codigo == nullptr) n[0] = 0;
    else strcpy(n, codigo);
}

void Producto::setCodigo(const char *n) {
    if (codigo != nullptr) delete codigo;
    codigo = new char [strlen(n) + 1]{};
    strcpy(codigo, n);
}

void Producto::getDescripcion(char *n) const {
    if (descripcion == nullptr) n[0] = 0;
    else strcpy(n, descripcion);
}

void Producto::setDescripcion(const char *n) {
    if (descripcion != nullptr) delete descripcion;
    descripcion = new char [strlen(n) + 1]{};
    strcpy(descripcion, n);
}

double Producto::getPrecio() const {
    return precio;
}

void Producto::setPrecio(double precio) {
    Producto::precio = precio;
}

int Producto::getStock() const {
    return stock;
}

void Producto::setStock(int stock) {
    Producto::stock = stock;
}

bool operator >> (ifstream &inArch, Producto &p) {
    char *bufCod, buff[200];
    inArch.getline(buff, 200, ',');
    if (inArch.eof()) return false;
    bufCod = new char [strlen (buff) + 1]{};
    strcpy(bufCod, buff);
    char *bufDes;
    inArch.getline(buff, 200, ',');
    bufDes = new char [strlen (buff) + 1]{};
    strcpy(bufDes, buff);
    int bufStock;
    double bufPrecio;
    char car;
    inArch >> bufPrecio >> car >> bufStock >> ws;
    p.setCodigo(bufCod);
    p.setDescripcion(bufDes);
    p.setPrecio(bufPrecio);
    p.setStock(bufStock);
    return true;
}
