//
// Created by marcos on 5/22/24.
//

#include "Cliente.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

Cliente::Cliente() {
    dni = 0;
    nombre = nullptr;
    telefono = 0;
    for (int i = 0; i < 200; i++) productosEntregados[i].inicializar();
    monto_total = 0;
}

int Cliente::getDni() const {
    return dni;
}

void Cliente::setDni(int dni) {
    Cliente::dni = dni;
}

void Cliente::getNombre(char *n) const {
    if (nombre == nullptr) n[0] = 0;
    else strcpy(n, nombre);
}

void Cliente::setNombre(const char *n) {
    if (nombre != nullptr) delete nombre;
    nombre = new char [strlen (n) + 1] {};
    strcpy(nombre, n);
}

int Cliente::getTelefono() const {
    return telefono;
}

void Cliente::setTelefono(int telefono) {
    Cliente::telefono = telefono;
}

bool operator >> (ifstream &inArch, Cliente &c) {
    int buffDni;
    inArch >> buffDni;
    if (inArch.eof()) return false;
    char car; inArch >> car;
    char *buffNom, buff[200];
    inArch.getline(buff, 200, ',');
    buffNom = new char [strlen (buff) + 1];
    strcpy(buffNom, buff);
    int buffTel; inArch >> buffTel >> ws;
    c.setDni(buffDni);
    c.setNombre(buffNom);
    c.setTelefono(buffTel);
    return true;
}

