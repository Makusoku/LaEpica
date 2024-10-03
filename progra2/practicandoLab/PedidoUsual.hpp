//
// Created by marcos on 6/14/24.
//

#ifndef PRACTICANDOLAB_PEDIDOUSUAL_HPP
#define PRACTICANDOLAB_PEDIDOUSUAL_HPP

#include "Pedido.hpp"
using namespace std;

class PedidoUsual : public Pedido {
private:
    double descuento;
    double flete;
public:
    PedidoUsual();

    ~PedidoUsual() override;

    double getDescuento() const;

    void setDescuento(double descuento);

    double getFlete() const;

    void setFlete(double flete);

    void lee (ifstream &arch);

    void imprime ();
};


#endif //PRACTICANDOLAB_PEDIDOUSUAL_HPP
