//
// Created by marcos on 6/19/24.
//

#ifndef PRAC2_ENCICLOPEDIA_HPP
#define PRAC2_ENCICLOPEDIA_HPP

#include "Libro.hpp"
using namespace std;

class Enciclopedia : public Libro {
private:
    int sku;
    int anho;
    int vigencia;

public:
    Enciclopedia();

    ~Enciclopedia() override;

    int getSku() const;

    void setSku(int sku);

    int getAnho() const;

    void setAnho(int anho);

    int getVigencia() const;

    void setVigencia(int vigencia);

    void lee (ifstream &arch);

    void imprime (ofstream &arch);

    void actualiza ();
};


#endif //PRAC2_ENCICLOPEDIA_HPP
