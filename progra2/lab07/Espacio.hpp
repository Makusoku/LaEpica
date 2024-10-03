//
// Created by marcos on 6/12/24.
//

#ifndef LAB07_ESPACIO_HPP
#define LAB07_ESPACIO_HPP


class Espacio {
private:
    char contenido;
    int posx;
    int posy;
public:
    Espacio();

    ~Espacio();

    char getContenido() const;

    void setContenido(char contenido);

    int getPosx() const;

    void setPosx(int posx);

    int getPosy() const;

    void setPosy(int posy);
};


#endif //LAB07_ESPACIO_HPP
