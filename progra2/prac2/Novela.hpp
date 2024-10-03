//
// Created by marcos on 6/19/24.
//

#ifndef PRAC2_NOVELA_HPP
#define PRAC2_NOVELA_HPP

#include "Libro.hpp"
using namespace std;


class Novela : public Libro {
private:
    char *autor;

public:
    Novela();

    ~Novela() override;

    void getAutor(char *) const;

    void setAutor(const char *autor);

    void lee (ifstream &arch);

    void imprime (ofstream &arch);

    void actualiza ();
};


#endif //PRAC2_NOVELA_HPP
