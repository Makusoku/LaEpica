//
// Created by marcos on 6/12/24.
//

#ifndef LAB07_ENCICLOPEDIA_HPP
#define LAB07_ENCICLOPEDIA_HPP

#include "Libro.hpp"
using namespace std;

class Enciclopedia : public Libro {
private:
    int volumen;
    double peso;

public:
    Enciclopedia();

    ~Enciclopedia();

    int getVolumen() const;

    void setVolumen(int volumen);

    double getPeso1() const;

    void setPeso1(double peso);

    void leerEnciclopedias (ifstream &arch);

};


#endif //LAB07_ENCICLOPEDIA_HPP
