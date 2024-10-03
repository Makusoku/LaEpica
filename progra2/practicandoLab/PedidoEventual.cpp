//
// Created by marcos on 6/14/24.
//

#include "PedidoEventual.hpp"

PedidoEventual::PedidoEventual() {
    flete = 0;
}

PedidoEventual::~PedidoEventual() {

}

double PedidoEventual::getFlete() const {
    return flete;
}

void PedidoEventual::setFlete(double flete) {
    PedidoEventual::flete = flete;
}

void PedidoEventual::lee(std::ifstream &arch) {
    arch >> flete;
    arch.get();
    Pedido::lee(arch);
}

void PedidoEventual::imprime() {
    cout << getCodigo() << " " << flete << " ";
}