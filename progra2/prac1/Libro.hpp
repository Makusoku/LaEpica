//
// Created by marcos on 6/17/24.
//

#ifndef PRAC1_LIBRO_HPP
#define PRAC1_LIBRO_HPP

#include "utils.hpp"
using namespace std;

class Libro {
private:
    char *codigo;
    char *nombre;
    int ancho;
    int alto;
    bool colocado;

public:
    Libro();
    virtual ~Libro();

    void getCodigo(char *) const;

    void setCodigo(const char *codigo);

    void getNombre(char *) const;

    void setNombre(const char *nombre);

    int getAncho() const;

    void setAncho(int ancho);

    int getAlto() const;

    void setAlto(int alto);

    bool isColocado() const;

    void setColocado(bool colocado);

    void leer_libro (ifstream &arch);

    void copiar (Libro &libro);
};

void operator >> (ifstream &arch, Libro &libro);
#endif //PRAC1_LIBRO_HPP
