//
// Created by marcos on 6/14/24.
//

#ifndef PRACTICANDOLAB_PEDIDOEVENTUAL_HPP
#define PRACTICANDOLAB_PEDIDOEVENTUAL_HPP

#include "Pedido.hpp"
using namespace std;

class PedidoEventual : public Pedido {
private:
    double flete;
public:
    PedidoEventual();

    ~PedidoEventual() override;

    double getFlete() const;

    void setFlete(double flete);

    void lee (ifstream &arch);

    void imprime ();
};


#endif //PRACTICANDOLAB_PEDIDOEVENTUAL_HPP
