//
// Created by marcos on 6/17/24.
//

#include "Estante.hpp"
using namespace std;

Estante::Estante() {
    codigo = nullptr;
    anchura = 0;
    altura = 0;
    espacios = nullptr;
    cantidad_libros = 0;
}

Estante::~Estante() {
    if (codigo != nullptr) delete codigo;
}

void Estante::getCodigo(char * n) const {
    if (codigo == nullptr) n[0] = 0;
    else strcpy (n, codigo);
}

void Estante::setCodigo(const char *n) {
    if (codigo != nullptr) delete codigo;
    codigo = new char [strlen (n) + 1]{};
    strcpy(codigo, n);
}

int Estante::getAnchura() const {
    return anchura;
}

void Estante::setAnchura(int anchura) {
    Estante::anchura = anchura;
}

int Estante::getAltura() const {
    return altura;
}

void Estante::setAltura(int altura) {
    Estante::altura = altura;
}

int Estante::getCantidadLibros() const {
    return cantidad_libros;
}

void Estante::setCantidadLibros(int cantidadLibros) {
    cantidad_libros = cantidadLibros;
}

void Estante::leer_estante(std::ifstream &arch) {
    char cod[200], car;
    arch.getline(cod, 200, ',');
    arch >> altura >> car >> anchura >> ws;
    setCodigo(cod);
}

void operator >> (ifstream &arch, Estante &estante) {
    estante.leer_estante(arch);
}

bool Estante::operator+=(Libro &libro) {

    if (espacios == nullptr) espacios = new Espacio [altura * anchura + 1]{};

    int altura_libro = libro.getAlto();
    int ancho_libro = libro.getAncho();
    int cant_actual = cantidad_restante_ancho();
    cout << cant_actual << endl;
    if (cumple_medidas(ancho_libro, altura_libro)){
        for (int i = 0; i < altura_libro; i++) {
            for (int j = 0; j < ancho_libro; j++) {
                int pos = (anchura - cant_actual + j) + anchura * (altura - i - 1);
                espacios[pos].setContenido('*');
                espacios[pos].setPosx(anchura - cant_actual + j);
                espacios[pos].setPosy(altura - i - 1);
            }
        }
        libros[cantidad_libros++].copiar (libro);
        return true;
    }
    return false;
}

int Estante::cantidad_restante_ancho () {
    int ans = 0;
    for (int i = 0; i < cantidad_libros; i++) {
        ans += libros[i].getAncho();
    }
    return anchura - ans;
}

bool Estante::cumple_medidas(int ancho_libro, int altura_libro) {
    return cantidad_restante_ancho() >= ancho_libro && altura >= altura_libro;
}


void Estante::imprimir(std::ofstream &arch) {
    for (int i = 0; i < altura * anchura; i++) {
        arch << espacios[i];
        if ((i + 1) % anchura ==  0) arch << endl;
    }
}

void operator << (ofstream &arch, Estante &estante) {
    estante.imprimir (arch);
}

void Estante::info_libro() {
    for (int i = 0; i < cantidad_libros; i++) {
        char a[200], b[200];
        libros[i].getNombre(a);
        libros[i].getCodigo(b);
        cout << libros[i].getAncho() << " " << libros[i].getAlto() << " " << a << " " << b << endl;
    }
}