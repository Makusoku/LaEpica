//
// Created by marcos on 6/19/24.
//

#ifndef PRAC2_REVISTA_HPP
#define PRAC2_REVISTA_HPP

#include "Libro.hpp"
using namespace std;

class Revista : public Libro {
private:
    int ISSN;
    int anho;
    int numero;
    int vigencia;

public:
    Revista();

    virtual ~Revista();

    int getIssn() const;

    void setIssn(int issn);

    int getAnho() const;

    void setAnho(int anho);

    int getNumero() const;

    void setNumero(int numero);

    int getVigencia() const;

    void setVigencia(int vigencia);

    void lee (ifstream &arch);

    void imprime (ofstream &arch);

    void actualiza ();
};


#endif //PRAC2_REVISTA_HPP
