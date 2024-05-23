//
// Created by marcos on 5/22/24.
//

#include <iostream>
#include "ClaseRectangulo.hpp"
using namespace std;
void ClaseRectangulo::asignarBase(double b) {
    base = b;
}

void ClaseRectangulo::asignarAltura(double h) {
    altura = h;
}

double ClaseRectangulo::entregarBase() {
    return base;
}

double ClaseRectangulo::entregarAltura() {
    return altura;
}

void ClaseRectangulo::leeDatos() {
    cout << "Ingrese la base: "; cin >> base;
    cout << "Ingrese la altura: "; cin >> altura;
}

void ClaseRectangulo::imprimeDatos() {
    cout.precision(2);
    cout << fixed;
    cout << "Base: " << base << endl;
    cout << "Altura: " << altura << endl;
}

double ClaseRectangulo::area() {
    return base*altura;
}

double ClaseRectangulo::perimetro() {
    return 2*(base + altura);
}

void ClaseRectangulo::imprimeResultados() {
    imprimeDatos();
    cout << "Area: " << area() << endl;
    cout << "Perimetro: " << perimetro() << endl;
}

