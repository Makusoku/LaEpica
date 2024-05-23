//
// Created by marcos on 5/22/24.
//

#ifndef LAB6_2023_2_V1_ALMACEN_HPP
#define LAB6_2023_2_V1_ALMACEN_HPP

#include "Cliente.hpp"
#include "Producto.hpp"

class Almacen {
private:
    Cliente arreglo_clientes[2000];
    int cantidad_clientes;
    Producto arreglo_productos[2000];
    int cantidad_productos;
};


#endif //LAB6_2023_2_V1_ALMACEN_HPP
