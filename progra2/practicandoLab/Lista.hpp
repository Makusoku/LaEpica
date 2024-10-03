//
// Created by marcos on 6/14/24.
//

#ifndef PRACTICANDOLAB_LISTA_HPP
#define PRACTICANDOLAB_LISTA_HPP

#include "Nodo.hpp"
using namespace std;

class Lista {
private:
    class Nodo *lini;
    class Nodo *lfin;
public:
    Lista();
    void lee_inserta (ifstream &, int);
    void insertar (Pedido *nuevo);
    void muestra ();
};


#endif //PRACTICANDOLAB_LISTA_HPP
