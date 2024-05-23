#include "Cadena.hpp"
#include <iostream>
using namespace std;

int main() {
    char n[222];

    // INICIALIZACION
    Cadena cad01;
    Cadena cad02 ("Ana Roncal");
    Cadena cad03 (10);
    Cadena cad04 = cad01;

    // ASIGNACION
    cad01.assign("Valentina");
    cad01.getDato(n);
    cout << n << endl;

    cad01.assign(cad02);
    cad01.getDato(n);
    cout << n << endl;

    cad01 = "Valentina";
    cad01.getDato(n);
    cout << n << endl;

    cad01 = cad02;
    cad01.getDato(n);
    cout << n << endl;

    cad01.append("Valentina");
    cad01.getDato(n);
    cout << n << endl;

    cad01.append(cad02);
    cad01.getDato(n);
    cout << n << endl;

    cad01.swap(cad02);
    cad01.getDato(n);
    cout << n << endl;

    cad02.getDato(n);
    cout << n << endl;

    // CONCATENACION
    cad03 = cad01 + cad02;
    cad03.getDato(n);
    cout << n << endl;

    // COMPARACION
    cout << cad01.compare("Naomi") << endl;
    cout << cad01.compare(cad02) << endl;

    cout << (cad01 == cad02) << " " << (cad01 == cad01) << endl;
    cout << (cad02 > cad01) << " " << (cad01 > cad01) << endl;
    cout << (cad01 < cad02) << " " << (cad01 < cad01) << endl;

    cout << (cad02 >= cad01) << " " << (cad01 >= cad01) << endl;
    cout << (cad01 <= cad02) << " " << (cad01 <= cad01) << endl;

    // LONGITUD
    cout << cad01.length() << endl;

    // IMPRESION
    cad01.print();
    cad02.print();
    return 0;
}
