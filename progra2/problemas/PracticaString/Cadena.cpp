//
// Created by marcos on 5/22/24.
//

#include "Cadena.hpp"
#include <cstring>
#include <iostream>
using namespace std;

Cadena::Cadena () {
    inicializarCadena ();
}

Cadena::Cadena(const char *n) {
    dato = new char [strlen (n) + 1]{};
    strcpy(dato, n);
    longitud = strlen (n);
    capacidad = strlen (n) + 1;
}

Cadena::Cadena(int n) {
    dato = new char [n]{};
    longitud = 0;
    capacidad = n;
}

Cadena::Cadena(const Cadena &obj) {
    char *n = new char [obj.getCapacidad()]{};
    obj.getDato (n);
    inicializarCadena();

    setDato (n);
    setLongitud (obj.getLongitud());
    setCapacidad (obj.getCapacidad());
}

Cadena::~Cadena() {
    eliminarDato();
}

void Cadena::eliminarDato() {
    if (dato != nullptr) delete dato;
}

void Cadena::inicializarCadena () {
    this->dato = nullptr;
    this->longitud = 0;
    this->capacidad = 0;
}

void Cadena::getDato(char *n) const {
    if (dato == nullptr) n[0] = 0;
    else strcpy (n, dato);
}

void Cadena::setDato(char *dato) {
    this->dato = dato;
}

int Cadena::getLongitud() const {
    return longitud;
}

void Cadena::setLongitud(int longitud) {
    this->longitud = longitud;
}

int Cadena::getCapacidad() const {
    return capacidad;
}

void Cadena::setCapacidad(int capacidad) {
    this->capacidad = capacidad;
}

void Cadena::assign(const char *nombre) {
    int n = strlen(nombre) + 1;
    if (getCapacidad() < n) {
        int nCap = 1.3 * (n - 1);
        char *a = new char [nCap]{};
        strcpy(a, nombre);
        setCapacidad(nCap);
        eliminarDato();
        setDato(a);
    }
    else strcpy (dato, nombre);
    setLongitud(strlen(nombre));
}

void Cadena::assign (const Cadena &obj) {
    char n[200];
    obj.getDato(n);

    if (getCapacidad() < obj.getLongitud() + 1) {
        int nCap = 1.3 * (obj.getLongitud());
        char *a = new char [nCap]{};
        strcpy(a, n);
        setCapacidad(nCap);
        eliminarDato();
        setDato(a);
    }
    else strcpy(dato, n);
    setLongitud(strlen(n));
}

void Cadena::operator = (const char *nombre) {
    int n = strlen(nombre) + 1;
    if (getCapacidad() < n) {
        int nCap = 1.3 * (n - 1);
        char *a = new char [nCap]{};
        strcpy(a, nombre);
        setCapacidad(nCap);
        eliminarDato();
        setDato(a);
    }
    else strcpy (dato, nombre);
    setLongitud(strlen(nombre));
}

void Cadena::operator = (const Cadena &obj) {
    char n[200];
    obj.getDato(n);

    if (getCapacidad() < obj.getLongitud() + 1) {
        int nCap = 1.3 * (obj.getLongitud());
        char *a = new char [nCap]{};
        strcpy(a, n);
        setCapacidad(nCap);
        eliminarDato();
        setDato(a);
    }
    else strcpy(dato, n);
    setLongitud(strlen(n));
}

void Cadena::append(const char *nombre) {
    int n = strlen(nombre) + 1;
    if (getCapacidad() < n + getLongitud() + 1) {
        int nCap = 1.3 * (n + getLongitud() - 1);
        char *a = new char [nCap]{};
        strcpy(a, dato);
        strcat(a, nombre);
        setCapacidad(nCap);
        eliminarDato();
        setDato(a);
    }
    else strcat(dato, nombre);
    setLongitud(getLongitud() + strlen(nombre));
}

void Cadena::append (const Cadena &obj) {
    char n[200];
    obj.getDato(n);

    if (getCapacidad() < obj.getLongitud() + 1 + getLongitud() + 1) {
        int nCap = 1.3 * (obj.getLongitud() + getLongitud());
        char *a = new char [nCap]{};
        strcpy(a, dato);
        strcat(a, n);
        setCapacidad(nCap);
        eliminarDato();
        setDato(a);
    }
    else strcat(dato, n);
    setLongitud(getLongitud() + obj.getLongitud());
}

void Cadena::swap (Cadena &obj) {
    Cadena aux = *this;
    assign(obj);
    obj.assign(aux);
}

Cadena Cadena::operator + (const Cadena &obj) {
    Cadena aux = *this;
    aux.append(obj);
    return aux;
}


int Cadena::compare (const char *c) {
    char n[200];
    getDato(n);
    return strcmp (n, c);
}

int Cadena::compare (const Cadena &obj) {
    char n[200];
    getDato(n);
    char n1[200];
    obj.getDato(n1);
    return strcmp (n, n1);
}

bool Cadena::operator == (const Cadena &obj) {
    char n[200];
    getDato(n);
    char n1[200];
    obj.getDato(n1);
    return strcmp (n, n1) == 0;
}

bool Cadena::operator > (const Cadena &obj) {
    char n[200];
    getDato(n);
    char n1[200];
    obj.getDato(n1);
    return strcmp (n, n1) > 0;
}

bool Cadena::operator < (const Cadena &obj) {
    char n[200];
    getDato(n);
    char n1[200];
    obj.getDato(n1);
    return strcmp (n, n1) < 0;
}

bool Cadena::operator >= (const Cadena &obj) {
    char n[200];
    getDato(n);
    char n1[200];
    obj.getDato(n1);
    return strcmp (n, n1) >= 0;
}

bool Cadena::operator <= (const Cadena &obj) {
    char n[200];
    getDato(n);
    char n1[200];
    obj.getDato(n1);
    return strcmp (n, n1) <= 0;
}

int Cadena::length () {
    return longitud;
}

void Cadena::print () {
    char n[200];
    getDato(n);
    cout << n << endl;
}