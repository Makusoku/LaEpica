#include <iostream>
#include <fstream>
using namespace std;
#include "Cliente.hpp"
#include "Producto.hpp"
#include "Pedido.hpp"

int main() {
    ifstream archDato ("Clientes.csv", ios :: in);
    if (!archDato.is_open()) {
        cout << "Error al abrir Clientes.csv" << endl;
        exit (1);
    }
    Cliente clientes[200];
    int i = 0;
    while (archDato >> clientes[i++]) ;

    for (int j = 0; j < i - 1; j++) {
        char n[200]; clientes[j].getNombre(n);
        cout << clientes[j].getDni() << " " << clientes[j].getTelefono() << " " << n << endl;
    }

    ifstream archDato2 ("Productos.csv", ios :: in);
    if (!archDato2.is_open()) {
        cout << "Error al abrir Productos.csv" << endl;
        exit (1);
    }

    Producto productos[200];
    i = 0;
    while (archDato2 >> productos[i++]) ;
    cout << endl << endl;
    for (int j = 0; j < i - 1; j++) {
        char a[200], b[200]; productos[j].getCodigo(a); productos[j].getDescripcion(b);
        cout << productos[j].getPrecio() << " " << productos[j].getStock() << " "
        << a << " " << b << endl;
    }

    ifstream archDato3 ("Pedidos.csv", ios :: in);
    if (!archDato3.is_open()) {
        cout << "Error al abrir Pedidos.csv" << endl;
        exit (1);
    }

    Pedido pedidos[600];
    i = 0;
    while (archDato3 >> pedidos[i++]) ;
    cout << endl << endl;
    for (int j = 0; j < i - 1; j++) {
        char a[200]; pedidos[j].getCodigo(a);
        cout << a << " " << pedidos[j].getDniCliente() << endl;
    }

    return 0;
}
