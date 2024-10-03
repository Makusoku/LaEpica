//
// Created by marcos on 6/12/24.
//

#ifndef LAB07_LIBRO_HPP
#define LAB07_LIBRO_HPP

#include "utils.hpp"
using namespace std;

class Libro {
private:
    char *codigo;
    char *nombre;
    int ancho;
    int alto;
    double peso;
    bool colocado;

public:

    Libro();

    ~Libro();

    bool isColocado() const;

    void setColocado(bool colocado);

    double getPeso() const;

    void setPeso(double peso);

    int getAlto() const;

    void setAlto(int alto);

    int getAncho() const;

    void setAncho(int ancho);

    void getNombre(char *n) const;

    void setNombre(const char *nombre);

    void getCodigo(char *n) const;

    void setCodigo(const char *codigo);

};


#endif //LAB07_LIBRO_HPP
