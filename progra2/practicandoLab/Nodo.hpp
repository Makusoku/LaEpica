//
// Created by marcos on 6/14/24.
//

#ifndef PRACTICANDOLAB_NODO_HPP
#define PRACTICANDOLAB_NODO_HPP

#include "Pedido.hpp"
using namespace std;

class Nodo {
private:
    class Pedido *ped;
    class Nodo *sig;
    class Nodo *ant;
public:
    Nodo();
    friend class Lista;
};


#endif //PRACTICANDOLAB_NODO_HPP
