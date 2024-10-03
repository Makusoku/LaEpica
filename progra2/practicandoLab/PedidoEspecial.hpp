//
// Created by marcos on 6/14/24.
//

#ifndef PRACTICANDOLAB_PEDIDOESPECIAL_HPP
#define PRACTICANDOLAB_PEDIDOESPECIAL_HPP

#include "Pedido.hpp"
using namespace std;

class PedidoEspecial : public Pedido {
private:
    double descuento;
public:
    PedidoEspecial();

    ~PedidoEspecial() override;

    double getDescuento() const;

    void setDescuento(double descuento);

    void lee (ifstream &arch);

    void imprime ();
};


#endif //PRACTICANDOLAB_PEDIDOESPECIAL_HPP
