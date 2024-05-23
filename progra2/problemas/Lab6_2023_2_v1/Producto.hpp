//
// Created by marcos on 5/22/24.
//

#ifndef LAB6_2023_2_V1_PRODUCTO_HPP
#define LAB6_2023_2_V1_PRODUCTO_HPP


class Producto {
private:
    char *codigo;
    char *descripcion;
    double precio;
    int stock;
    int clientes_servidos[2000];
    int clientes_no_servidos[2000];
    int cantidad_clientes_servidos;
    int cantidad_clientes_no_servidos;

public:

    Producto();
    ~Producto();
    void getCodigo(char *) const;

    void setCodigo(const char *codigo);

    void getDescripcion(char *) const;

    void setDescripcion(const char *descripcion);

    double getPrecio() const;

    void setPrecio(double precio);

    int getStock() const;

    void setStock(int stock);

};

bool operator >> (ifstream &, Producto &p);

#endif //LAB6_2023_2_V1_PRODUCTO_HPP
