//
// Created by marcos on 6/17/24.
//

#ifndef PRAC1_ESTANTE_HPP
#define PRAC1_ESTANTE_HPP

#include "utils.hpp"
#include "Libro.hpp"
#include "Espacio.hpp"
using namespace std;

class Estante {
private:
    char *codigo;
    int anchura;
    int altura;
    Libro libros[50];
    Espacio *espacios;
    int cantidad_libros;

public:
    Estante();

    virtual ~Estante();

    void getCodigo(char *) const;

    void setCodigo(const char *codigo);

    int getAnchura() const;

    void setAnchura(int anchura);

    int getAltura() const;

    void setAltura(int altura);

    int getCantidadLibros() const;

    void setCantidadLibros(int cantidadLibros);

    void leer_estante (ifstream &arch);

    bool operator += (Libro &libro);

    int cantidad_restante_ancho ();

    bool cumple_medidas (int ancho_libro, int altura_libro);

    void imprimir (ofstream &arch);

    void info_libro ();
};


void operator >> (ifstream &arch, Estante &estante);
void operator << (ofstream &arch, Estante &estante);
#endif //PRAC1_ESTANTE_HPP
