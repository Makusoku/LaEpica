cmake_minimum_required(VERSION 3.28)
project(Lab6_2023_2_v1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab6_2023_2_v1 main.cpp
        ProductoEntregado.cpp
        ProductoEntregado.hpp
        Cliente.cpp
        Cliente.hpp
        Producto.cpp
        Producto.hpp
        Pedido.cpp
        Pedido.hpp
        Almacen.cpp
        Almacen.hpp
)
