//
// Created by marcos on 5/22/24.
//

#ifndef POOTEORIA_CLASERECTANGULO_HPP
#define POOTEORIA_CLASERECTANGULO_HPP


class ClaseRectangulo {
private:
    double base;
    double altura;

public:
    void asignarBase (double);
    void asignarAltura (double);
    void leeDatos (void);
    double entregarBase (void);
    double entregarAltura (void);


    void imprimeDatos (void);
    double area (void);
    double perimetro (void);
    void imprimeResultados (void);
};


#endif //POOTEORIA_CLASERECTANGULO_HPP
