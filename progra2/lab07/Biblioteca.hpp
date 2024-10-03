//
// Created by marcos on 6/12/24.
//

#ifndef LAB07_BIBLIOTECA_HPP
#define LAB07_BIBLIOTECA_HPP

#include "EstanteVertical.hpp"
#include "EstanteHorizontal.hpp"
using namespace std;

class Biblioteca {
private:
    EstanteVertical estantesVerticales[50];
    int cantidad_estantes_verticales;
    EstanteHorizontal estantesHorizontales[50];
    int cantidad_estantes_horizontales;
    Enciclopedia enciclopedias[50];
    int cantidad_total_enciclopedias;
    Novela novelas[50];
    int cantidad_total_novelas;

public:
    Biblioteca();
    ~Biblioteca();

    int getCantidadEstantesVerticales() const;

    void setCantidadEstantesVerticales(int cantidadEstantesVerticales);

    int getCantidadEstantesHorizontales() const;

    void setCantidadEstantesHorizontales(int cantidadEstantesHorizontales);

    int getCantidadTotalEnciclopedias() const;

    void setCantidadTotalEnciclopedias(int cantidadTotalEnciclopedias);

    int getCantidadTotalNovelas() const;

    void setCantidadTotalNovelas(int cantidadTotalNovelas);

    // Resolucion

    void cargar_libros ();
    void cargar_estantes ();
    void posicionar_libros ();

    // Auxiliares
    bool hayEspacioSuficiente (Enciclopedia enciclopedias, int n);
};


#endif //LAB07_BIBLIOTECA_HPP
