//
// Created by marcos on 6/19/24.
//

#ifndef PRAC2_LIBRO_HPP
#define PRAC2_LIBRO_HPP

#include "utils.hpp"
using namespace std;

class Libro {
private:
    char *nombre;
    int paginas;
    double peso;

public:
    Libro();

    virtual ~Libro();

    void getNombre(char *) const;

    void setNombre(const char *nombre);

    int getPaginas() const;

    void setPaginas(int paginas);

    double getPeso() const;

    void setPeso(double peso);

    virtual void lee (ifstream &arch);

    virtual void imprime (ofstream &arch);

    virtual void actualiza () = 0;
};


#endif //PRAC2_LIBRO_HPP
