//
// Created by marcos on 6/12/24.
//

#ifndef LAB07_NOVELA_HPP
#define LAB07_NOVELA_HPP

#include "Libro.hpp"
using namespace std;

class Novela : public Libro {
private:
    char *tipo;
    double peso;

public:
    Novela();
    ~Novela();

    void getTipo(char *) const;

    void setTipo(const char *tipo);

    double getPeso1() const;

    void setPeso1(double peso);

    //Resolucion
    void leerLibros (ifstream &arch);

};


#endif //LAB07_NOVELA_HPP
