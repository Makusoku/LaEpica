//
// Created by marcos on 6/19/24.
//

#include "Revista.hpp"
using namespace std;

Revista::Revista() {
    ISSN = 0;
    anho = 0;
    vigencia = 1;
    numero = 0;
}

Revista::~Revista() {

}

int Revista::getIssn() const {
    return ISSN;
}

void Revista::setIssn(int issn) {
    ISSN = issn;
}

int Revista::getAnho() const {
    return anho;
}

void Revista::setAnho(int anho) {
    Revista::anho = anho;
}

int Revista::getNumero() const {
    return numero;
}

void Revista::setNumero(int numero) {
    Revista::numero = numero;
}

int Revista::getVigencia() const {
    return vigencia;
}

void Revista::setVigencia(int vigencia) {
    Revista::vigencia = vigencia;
}

void Revista::lee(std::ifstream &arch) {
    Libro::lee(arch);
    char car;
    arch >> ISSN >> car >> anho >> car >> numero >> ws;
}

void Revista::imprime(std::ofstream &arch) {
    Libro::imprime(arch);
    arch << "ISSN: " << ISSN << setw(20) << "Ano: " << anho << setw(20) << "Numero: " << numero << setw(20)
    << "Vigencia: " << vigencia << endl << endl;
}

void Revista::actualiza() {
    if (anho <= 2020) vigencia = 0;
}