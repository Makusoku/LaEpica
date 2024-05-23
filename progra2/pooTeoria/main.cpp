#include <iostream>
#include "ClaseRectangulo.hpp"
using namespace std;

int main() {

    ClaseRectangulo rectangulo, rct1;
    rectangulo.asignarBase(235.5);
    rectangulo.asignarAltura(456.13);
//    rectangulo.imprimeResultados();

    // Se le asignan los datos de rectangulo a rct1
    rct1 = rectangulo;
    rct1.imprimeResultados();

    return 0;
}

