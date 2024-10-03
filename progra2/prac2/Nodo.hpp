//
// Created by marcos on 6/19/24.
//

#ifndef PRAC2_NODO_HPP
#define PRAC2_NODO_HPP

#include "Libro.hpp"
#include "Lista.hpp"
using namespace std;

class Nodo {
private:
    Libro *plibro;
    class Nodo *sig;

public:
    Nodo();

    friend class Lista;


};


#endif //PRAC2_NODO_HPP
