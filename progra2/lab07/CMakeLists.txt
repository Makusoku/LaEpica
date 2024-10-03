cmake_minimum_required(VERSION 3.28)
project(lab07)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab07 main.cpp
        Libro.cpp
        Libro.hpp
        utils.hpp
        Enciclopedia.cpp
        Enciclopedia.hpp
        Novela.cpp
        Novela.hpp
        Espacio.cpp
        Espacio.hpp
        Estante.cpp
        Estante.hpp
        EstanteVertical.cpp
        EstanteVertical.hpp
        EstanteHorizontal.cpp
        EstanteHorizontal.hpp
        Biblioteca.cpp
        Biblioteca.hpp)
