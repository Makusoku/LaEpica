//
// Created by marcos on 6/19/24.
//

#ifndef PRAC2_BIBLIOTECA_HPP
#define PRAC2_BIBLIOTECA_HPP

#include "Estante.hpp"
using namespace std;

class Biblioteca {
private:
    class Estante AEstantes[10];

public:

    Biblioteca();

    void reserva_memoria (ifstream &arch, char tipo);


// Solucion
    void carga ();
    void llena ();
    void baja ();
    void muestra ();
};


#endif //PRAC2_BIBLIOTECA_HPP
