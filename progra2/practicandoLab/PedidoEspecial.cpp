//
// Created by marcos on 6/14/24.
//

#include "PedidoEspecial.hpp"

PedidoEspecial::PedidoEspecial() {
    descuento = 0;
}

PedidoEspecial::~PedidoEspecial() {

}

double PedidoEspecial::getDescuento() const {
    return descuento;
}

void PedidoEspecial::setDescuento(double descuento) {
    PedidoEspecial::descuento = descuento;
}

void PedidoEspecial::lee(std::ifstream &arch) {
    arch >> descuento;
    arch.get();
    Pedido::lee(arch);
}

void PedidoEspecial::imprime() {
    cout << getCodigo() << " " <<descuento << " ";
}