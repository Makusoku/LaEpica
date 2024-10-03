//
// Created by marcos on 6/14/24.
//

#include "PedidoUsual.hpp"

PedidoUsual::PedidoUsual() {
    descuento = 0;
    flete = 0;
}

PedidoUsual::~PedidoUsual() {

}

double PedidoUsual::getDescuento() const {
    return descuento;
}

void PedidoUsual::setDescuento(double descuento) {
    PedidoUsual::descuento = descuento;
}

double PedidoUsual::getFlete() const {
    return flete;
}

void PedidoUsual::setFlete(double flete) {
    PedidoUsual::flete = flete;
}

void PedidoUsual::lee(std::ifstream &arch) {
    char car;
    arch >> descuento >> car >> flete;
    arch.get();
    Pedido::lee(arch);
}

void PedidoUsual::imprime() {
    cout << getCodigo() << " " << flete << " " << descuento << " ";
}