//
// Created by marcos on 6/12/24.
//

#ifndef LAB07_ESTANTE_HPP
#define LAB07_ESTANTE_HPP

#include "utils.hpp"
#include "Espacio.hpp"
using namespace std;


class Estante {

private:
    char *codigo;
    int anchura;
    int altura;
    Espacio *espacios;
    double pesoSoportado;
    double pesoActual;

public:
    Estante();
    ~Estante();

    void getCodigo(char * n) const;

    void setCodigo(const char *codigo);

    int getAnchura() const;

    void setAnchura(int anchura);

    int getAltura() const;

    void setAltura(int altura);

    double getPesoSoportado() const;

    void setPesoSoportado(double pesoSoportado);

    double getPesoActual() const;

    void setPesoActual(double pesoActual);

    void leerEstante (ifstream &arch);
};


#endif //LAB07_ESTANTE_HPP
