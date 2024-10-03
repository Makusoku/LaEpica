//
// Created by marcos on 6/19/24.
//

#include "Enciclopedia.hpp"
using namespace std;

Enciclopedia::Enciclopedia() {
    sku = 0;
    anho = 0;
    vigencia = 1;
}

Enciclopedia::~Enciclopedia() {

}

int Enciclopedia::getSku() const {
    return sku;
}

void Enciclopedia::setSku(int sku) {
    Enciclopedia::sku = sku;
}

int Enciclopedia::getAnho() const {
    return anho;
}

void Enciclopedia::setAnho(int anho) {
    Enciclopedia::anho = anho;
}

int Enciclopedia::getVigencia() const {
    return vigencia;
}

void Enciclopedia::setVigencia(int vigencia) {
    Enciclopedia::vigencia = vigencia;
}

void Enciclopedia::lee(std::ifstream &arch) {
    char car;
    Libro::lee(arch);
    arch >> sku >> car >> anho >> ws;
}

void Enciclopedia::imprime(std::ofstream &arch) {
    Libro::imprime(arch);
    arch << "SKU: " << sku << setw(20) << "Ano: " << anho << setw(20) << "Vigencia: " << vigencia << endl << endl;
}

void Enciclopedia::actualiza() {
    if (anho <= 2020) vigencia = 0;
}