//
// Created by marcos on 6/14/24.
//

#include "Pedido.hpp"

Pedido::Pedido() {
    codigo = 0;
    nombre = nullptr;
    cantidad = 0;
    dni = 0;
    fecha = 0;
    total = 0;
}

Pedido::~Pedido() {
    if (nombre != nullptr) delete nombre;
}

int Pedido::getCodigo() const {
    return codigo;
}

void Pedido::setCodigo(int codigo) {
    Pedido::codigo = codigo;
}

void Pedido::getNombre(char * n) const {
    if (nombre == nullptr) n[0] = 0;
    else strcpy (n, nombre);
}

void Pedido::setNombre(const char *n) {
    if (nombre != nullptr) delete nombre;
    nombre = new char [strlen (n) + 1]{};
    strcpy(nombre, n);
}

int Pedido::getCantidad() const {
    return cantidad;
}

void Pedido::setCantidad(int cantidad) {
    Pedido::cantidad = cantidad;
}

int Pedido::getDni() const {
    return dni;
}

void Pedido::setDni(int dni) {
    Pedido::dni = dni;
}

int Pedido::getFecha() const {
    return fecha;
}

void Pedido::setFecha(int fecha) {
    Pedido::fecha = fecha;
}

double Pedido::getTotal() const {
    return total;
}

void Pedido::setTotal(double total) {
    Pedido::total = total;
}

void Pedido::lee(std::ifstream &arch) {
    char nom[100], car;
    int dd, mm, aa;
    arch.getline(nom, 100, ',');
    arch >> cantidad >> car >> total >> car >> dni >> car >> dd >> car >> mm >> car >> aa >> ws;
    setNombre(nom);
    setFecha(aa*10000+mm*100+dd);
}

void Pedido::imprime() {
    cout << nombre << " " << cantidad << " " << total << " " << dni << " " << fecha << endl;
}

bool Pedido::cmp(Pedido *p) {
    cout << p->nombre << " " << nombre << endl;
    return false;
}