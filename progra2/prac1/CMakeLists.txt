cmake_minimum_required(VERSION 3.28)
project(prac1)

set(CMAKE_CXX_STANDARD 17)

add_executable(prac1 main.cpp
        utils.hpp
        Libro.cpp
        Libro.hpp
        Espacio.cpp
        Espacio.hpp
        Estante.cpp
        Estante.hpp
        Biblioteca.cpp
        Biblioteca.hpp)
