//
// Created by marcos on 6/17/24.
//

#ifndef PRAC1_BIBLIOTECA_HPP
#define PRAC1_BIBLIOTECA_HPP

#include "utils.hpp"
#include "Estante.hpp"
#include "Libro.hpp"
using namespace std;

class Biblioteca {
private:
    Estante estantes[50];
    int cantidad_estantes;
    Libro libros[50];
    int cantidad_libros;

public:
    Biblioteca();

    virtual ~Biblioteca();

    int getCantidadEstantes() const;

    void setCantidadEstantes(int cantidadEstantes);

    int getCantidadLibros() const;

    void setCantidadLibros(int cantidadLibros);
};


#endif //PRAC1_BIBLIOTECA_HPP
