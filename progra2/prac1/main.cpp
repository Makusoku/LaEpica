#include "Biblioteca.hpp"

int main() {
    Biblioteca biblioteca;

    ifstream arch ("libros.csv", ios :: in);
    if (!arch.is_open()) {
        cout << "Error al abrir libros.csv" << endl;
        exit (1);
    }
    Libro libros;
    arch >> libros;
    cout << libros.getAlto() << " " << libros.getAncho() << endl;

    Estante estantes;

    ifstream archE ("estantes.csv", ios :: in);
    archE >> estantes;
    estantes += libros;
    arch >> libros;
    estantes += libros;

    arch >> libros;
    estantes += libros;


    ofstream archRep ("reporte.txt", ios :: out);
    archRep << estantes;

    estantes.info_libro();
    return 0;
}


