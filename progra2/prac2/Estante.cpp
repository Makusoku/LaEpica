//
// Created by marcos on 6/19/24.
//

#include "Estante.hpp"
using namespace std;

Estante::Estante() {
    clase = ' ';
    id = 0;
    capacidad = 0;
}

void Estante::leer_estante (ifstream &arch) {
    char car;
    arch >> clase;
    if (arch.eof()) return;
    arch >> car >> id >> car >> capacidad >> ws;
}

char Estante::getClase() const {
    return clase;
}

void Estante::setClase(char clase) {
    Estante::clase = clase;
}

int Estante::getId() const {
    return id;
}

void Estante::setId(int id) {
    Estante::id = id;
}

double Estante::getCapacidad() const {
    return capacidad;
}

void Estante::setCapacidad(double capacidad) {
    Estante::capacidad = capacidad;
}

bool Estante::inserta_libro(class Libro *nuevo) {
    int peso_actual = Llibros.getPeso ();
    if (nuevo->getPeso() <= capacidad - peso_actual) {
        Llibros.inserta_elemento (nuevo);
        return true;
    }
    return false;
}

void Estante::mostrar(std::ofstream &arch) {
    for (int i = 0; i < 90; i++) arch << "=";
    arch << endl;

    arch << "Id: " << id << endl;
    arch << "Tipo: " << clase << endl;
    arch << "Capacidad: " << capacidad << endl;
    arch << "Libros Contenidos: " << endl;
    for (int j = 0; j <= 90; j++) arch << "=";
    arch << endl;

    Llibros.imprime_lista(arch);

}

void Estante::baja_vigencia() {
    Llibros.baja_vigencia_libro();
}