//
// Created by marcos on 6/14/24.
//

#ifndef PRACTICANDOLAB_PEDIDO_HPP
#define PRACTICANDOLAB_PEDIDO_HPP

#include "utils.hpp"
using namespace std;

class Pedido {
private:
    int codigo;
    char *nombre;
    int cantidad;
    int dni;
    int fecha;
    double total;
public:
    Pedido();

    virtual ~Pedido();

    int getCodigo() const;

    void setCodigo(int codigo);

    void getNombre(char *) const;

    void setNombre(const char *nombre);

    int getCantidad() const;

    void setCantidad(int cantidad);

    int getDni() const;

    void setDni(int dni);

    int getFecha() const;

    void setFecha(int fecha);

    double getTotal() const;

    void setTotal(double total);

    virtual void lee (ifstream &);

    virtual void imprime ();

    bool cmp (Pedido *p);
};


#endif //PRACTICANDOLAB_PEDIDO_HPP
