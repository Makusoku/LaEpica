//
// Created by marcos on 6/19/24.
//

#ifndef PRAC2_ESTANTE_HPP
#define PRAC2_ESTANTE_HPP

#include "utils.hpp"
#include "Lista.hpp"
using namespace std;

class Estante {
private:
    char clase;
    int id;
    double capacidad;
    class Lista Llibros;

public:
    Estante();

    char getClase() const;

    void setClase(char clase);

    int getId() const;

    void setId(int id);

    double getCapacidad() const;

    void setCapacidad(double capacidad);

    void leer_estante (ifstream &arch);

    bool inserta_libro (class Libro *nuevo);

    void mostrar (ofstream &arch);

    void baja_vigencia ();
};


#endif //PRAC2_ESTANTE_HPP
