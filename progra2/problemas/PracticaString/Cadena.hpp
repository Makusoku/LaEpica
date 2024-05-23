//
// Created by marcos on 5/22/24.
//

#ifndef PRACTICASTRING_CADENA_HPP
#define PRACTICASTRING_CADENA_HPP


class Cadena {
private:
    char *dato;
    int longitud;
    int capacidad;
public:
    // Hay 3 tipos de constructores
    Cadena ();                  // Sin parametros
    Cadena (const char *);     // Con parametros
    Cadena (int);
    Cadena (const Cadena &);        // Copia

    // Destructor
    ~Cadena();

    void eleminarDato ();

    void inicializarCadena ();

    void getDato(char *) const;

    void setDato(char *dato);

    int getLongitud() const;

    void setLongitud(int longitud);

    int getCapacidad() const;

    void setCapacidad(int capacidad);

    void assign (const char *);

    void assign (const Cadena &);

    void append (const char *);

    void append (const Cadena &);

    void swap (Cadena &);

    void operator = (const char *);

    void operator = (const Cadena &);

    Cadena operator + (const Cadena &);

    int compare (const char *);

    int compare (const Cadena &);

    bool operator == (const Cadena &);

    bool operator > (const Cadena &);

    bool operator < (const Cadena &);

    bool operator >= (const Cadena &);

    bool operator <= (const Cadena &);

    int length ();

    void print ();
};


#endif //PRACTICASTRING_CADENA_HPP
