//
// Created by marcos on 6/19/24.
//

#include "Biblioteca.hpp"
#include "Revista.hpp"
#include "Enciclopedia.hpp"
#include "Novela.hpp"
using namespace std;

Biblioteca::Biblioteca() {

}

void Biblioteca::carga() {
    ifstream arch("Estantes2.csv", ios::in);
    if (!arch.is_open()) {
        cout << "Error al abrir Estantes2.csv" << endl;
        exit(1);
    }
    int i = 0;
    char tipo;
    while (1) {
        AEstantes[i++].leer_estante(arch);
        if (arch.eof()) break;
    }
}

void Biblioteca::llena() {
    ifstream arch("Libros3.csv", ios::in);
    if (!arch.is_open()) {
        cout << "Error al abrir Libros3.csv" << endl;
        exit(1);
    }
    char tipo;

    while (1) {
        arch >> tipo;
        if (arch.eof()) break;
        reserva_memoria(arch, tipo);
    }
}

void Biblioteca::reserva_memoria(std::ifstream &arch, char tipo) {
    Libro *nuevo;
    if (tipo == 'E') nuevo = new class Enciclopedia;
    if (tipo == 'N') nuevo = new class Novela;
    if (tipo == 'R') nuevo = new class Revista;
    nuevo->lee(arch);

    for (int i = 0; i < 10; i++) {
        if (AEstantes[i].inserta_libro (nuevo)) return;
    }
    delete nuevo;
}

void Biblioteca::muestra() {
    ofstream arch ("Reporte.txt", ios :: out);
    if (!arch.is_open()) {
        cout << "Error al abrir Reporte.txt" << endl;
        exit (1);
    }
    arch << "Estantes" << endl;
    int i = 0;
    while (1) {
        if (AEstantes[i].getCapacidad() == 0) break;
        AEstantes[i++].mostrar (arch);
    }
}

void Biblioteca::baja() {
    int i = 0;
    while (1) {
        if (AEstantes[i].getCapacidad() == 0) break;
        AEstantes[i++].baja_vigencia ();
    }
}