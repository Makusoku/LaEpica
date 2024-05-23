//
// Created by marcos on 5/22/24.
//

#ifndef LAB6_2023_2_V1_PEDIDO_HPP
#define LAB6_2023_2_V1_PEDIDO_HPP

#include <fstream>
using namespace std;

class Pedido {
private:
    char *codigo;
    int dni_cliente;
    double precio_producto;
public:
    int getDniCliente() const;

    void setDniCliente(int dniCliente);

    void getCodigo(char *n) const;

    void setCodigo(const char *codigo);

public:
    Pedido();
};

bool operator >> (ifstream &, Pedido &p);

#endif //LAB6_2023_2_V1_PEDIDO_HPP
