//
// Created by marcos on 6/19/24.
//

#ifndef PRAC2_LISTA_HPP
#define PRAC2_LISTA_HPP

#include "Nodo.hpp"
using namespace std;

class Lista {
private:
    double peso;
    class Nodo *ini;

public:
    Lista();

    double getPeso() const;

    void setPeso(double peso);

    void inserta_elemento (class Libro *nuevo);

    void imprime_lista (ofstream &arch);

    void baja_vigencia_libro ();
};


#endif //PRAC2_LISTA_HPP
