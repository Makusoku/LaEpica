//
// Created by marcos on 6/12/24.
//

#include "Biblioteca.hpp"
using namespace std;

Biblioteca::Biblioteca() {
    cantidad_estantes_horizontales = 0;
    cantidad_estantes_verticales = 0;
    cantidad_total_enciclopedias = 0;
    cantidad_total_novelas = 0;
}

Biblioteca::~Biblioteca() {
}

int Biblioteca::getCantidadEstantesVerticales() const {
    return cantidad_estantes_verticales;
}

void Biblioteca::setCantidadEstantesVerticales(int cantidadEstantesVerticales) {
    cantidad_estantes_verticales = cantidadEstantesVerticales;
}

int Biblioteca::getCantidadEstantesHorizontales() const {
    return cantidad_estantes_horizontales;
}

void Biblioteca::setCantidadEstantesHorizontales(int cantidadEstantesHorizontales) {
    cantidad_estantes_horizontales = cantidadEstantesHorizontales;
}

int Biblioteca::getCantidadTotalEnciclopedias() const {
    return cantidad_total_enciclopedias;
}

void Biblioteca::setCantidadTotalEnciclopedias(int cantidadTotalEnciclopedias) {
    cantidad_total_enciclopedias = cantidadTotalEnciclopedias;
}

int Biblioteca::getCantidadTotalNovelas() const {
    return cantidad_total_novelas;
}

void Biblioteca::setCantidadTotalNovelas(int cantidadTotalNovelas) {
    cantidad_total_novelas = cantidadTotalNovelas;
}

// Resolucion

void Biblioteca::cargar_libros() {
    ifstream archDato ("libros2.csv", ios :: in);
    if (!archDato.is_open()) {
        cout << "Error al abrir libros2.csv" << endl;
        exit (1);
    }
    int cant_novela = 0, cant_enciclopedia = 0;
    char tipo_libro;
    while (1) {
        tipo_libro = archDato.get();
        if (archDato.eof()) break;
        if (tipo_libro == 'N') novelas[cant_novela++].leerLibros(archDato);
        else enciclopedias[cant_enciclopedia++].leerEnciclopedias(archDato);
    }
    setCantidadTotalEnciclopedias(cant_enciclopedia);
    setCantidadTotalNovelas(cant_novela);
}

void Biblioteca::cargar_estantes() {
    ifstream archDato ("estantes2.csv", ios :: in);
    if (!archDato.is_open()) {
        cout << "Error al abrir estantes2.csv" << endl;
        exit (1);
    }
    int cant_vertical = 0, cant_horizontal = 0;
    char tipo_estante;
    while (1) {
        tipo_estante = archDato.get();
        if (archDato.eof()) break;
        if (tipo_estante == 'H') estantesHorizontales[cant_horizontal++].leerEstante(archDato);
        else estantesVerticales[cant_vertical++].leerEstante(archDato);
    }
    setCantidadEstantesHorizontales(cant_horizontal);
    setCantidadEstantesVerticales(cant_vertical);
}



void Biblioteca::posicionar_libros() {

    // Vertical -> Enciclopedia
    int numEstante = 0;
    for (int i = 0; i < getCantidadTotalEnciclopedias(); i++) {
        if (hayEspacioSuficiente (enciclopedias[i], numEstante)) {

        }
    }

}

bool Biblioteca::hayEspacioSuficiente(Enciclopedia enciclopedia, int numEstante) {

    while (numEstante < getCantidadEstantesVerticales()) {
        if (verificarCondiciones (estantesVerticales[numEstante], enciclopedia)) {
            enciclopedia.setColocado(true);
            estantesVerticales[numEstante].setPesoActual(enciclopedia.getPeso());
            return true;
        }
        numEstante++;
    }
    return false;
}