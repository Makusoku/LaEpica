cmake_minimum_required(VERSION 3.28)
project(algo)

set(CMAKE_CXX_STANDARD 17)

add_executable(algo main.cpp
        NodoArbol.h
        ArbolBinario.h
        funcionesArbolesBinarios.h
        funcionesArbolesBinarios.cpp
)
