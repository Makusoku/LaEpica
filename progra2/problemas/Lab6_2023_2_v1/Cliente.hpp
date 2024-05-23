//
// Created by marcos on 5/22/24.
//

#ifndef LAB6_2023_2_V1_CLIENTE_HPP
#define LAB6_2023_2_V1_CLIENTE_HPP

#include "ProductoEntregado.hpp"
#include <fstream>
using namespace std;

class Cliente {
private:
    int dni;
    char *nombre;
    int telefono;
    ProductoEntregado productosEntregados[200];
    int cantidad_productos_entregados;
    double monto_total;

public:
    Cliente();

    int getDni() const;

    void setDni(int dni);

    void getNombre(char *) const;

    void setNombre(const char *nombre);

    int getTelefono() const;

    void setTelefono(int telefono);
};

bool operator >> (ifstream &, Cliente &c);

#endif //LAB6_2023_2_V1_CLIENTE_HPP
