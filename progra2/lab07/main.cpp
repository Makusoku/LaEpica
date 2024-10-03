#include "Biblioteca.hpp"
using namespace std;

int main() {
    Biblioteca biblioteca;

    biblioteca.cargar_libros();
    biblioteca.cargar_estantes();
    biblioteca.posicionar_libros();

    return 0;
}
