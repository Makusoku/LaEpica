/*
 * File:   main.cpp
 * Author: ANA RONCAL
 * Created on 18 de septiembre de 2023, 05:39 PM
 */

#include <iostream>
#include "ArbolBinario.h"
using namespace std;
#include "funcionesArbolesBinarios.h"
/*
 * ESTRUCTURA ÁRBOL BINARIO 2024-1
 */
int main(int argc, char** argv) {

    struct ArbolBinario arbol;
    construir(arbol);

    plantarArbolBinario(arbol, nullptr, 'L', nullptr);

    struct ArbolBinario arbol1, arbol2, arbol3, arbol4, arbol5, arbol6, arbol7, arbol8, arbol9;

    plantarArbolBinario(arbol1, nullptr, 'T', nullptr);
    plantarArbolBinario(arbol2, nullptr, 'G', nullptr);

    plantarArbolBinario(arbol3, arbol1, 'S', arbol2);
    plantarArbolBinario(arbol4, nullptr, 'W', nullptr);

    plantarArbolBinario(arbol1, nullptr, 'E', nullptr);
    plantarArbolBinario(arbol2, nullptr, 'S', nullptr);
    plantarArbolBinario(arbol3, arbol1, 'S', arbol2);
    plantarArbolBinario(arbol4, nullptr, 'W', nullptr);


    plantarArbolBinario(arbol1, nullptr, 'E', nullptr);
    plantarArbolBinario(arbol2, nullptr, 'S', nullptr);
    plantarArbolBinario(arbol3, arbol1, 'S', arbol2);
    plantarArbolBinario(arbol4, nullptr, 'W', nullptr);

    plantarArbolBinario(arbol1, nullptr, 'E', nullptr);
    plantarArbolBinario(arbol2, nullptr, 'S', nullptr);
    plantarArbolBinario(arbol3, arbol1, 'S', arbol2);
    plantarArbolBinario(arbol4, nullptr, 'W', nullptr);
    plantarArbolBinario(arbol, arbol3, 'L', arbol4);

    cout<<"Recorrer en pre orden: "<<endl;
    recorrerPreOrden(arbol); cout<<endl;
    cout<<"Recorrer en orden: "<<endl;
    recorrerEnOrden(arbol); cout<<endl;
    cout<<"Recorrer en post orden: "<<endl;
    recorrerPostOrden(arbol); cout<<endl;

    cout<<"ALTURA árbol: "<<altura(arbol)<<endl;
    cout<<"NúMERO DE HOJAS: "<<numeroHojas(arbol)<<endl;
    cout<<"NúMERO DE NODOS: "<<numeroNodos(arbol)<<endl;
    cout<<"ES EQUILIBRADO: "<<esEquilibrado(arbol)<<endl;

    destruirArbolBinario(arbol);
    cout<<"Es árbol vacío: "<<esArbolVacio(arbol)<<endl;

    return 0;
}

