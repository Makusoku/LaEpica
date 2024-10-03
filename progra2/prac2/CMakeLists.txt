cmake_minimum_required(VERSION 3.28)
project(prac2)

set(CMAKE_CXX_STANDARD 17)

add_executable(prac2 main.cpp
        Libro.cpp
        Libro.hpp
        utils.hpp
        Enciclopedia.cpp
        Enciclopedia.hpp
        Novela.cpp
        Novela.hpp
        Revista.cpp
        Revista.hpp
        Nodo.cpp
        Nodo.hpp
        Lista.cpp
        Lista.hpp
        Estante.cpp
        Estante.hpp
        Biblioteca.cpp
        Biblioteca.hpp)
