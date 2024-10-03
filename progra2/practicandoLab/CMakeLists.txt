cmake_minimum_required(VERSION 3.28)
project(practicandoLab)

set(CMAKE_CXX_STANDARD 17)

add_executable(practicandoLab main.cpp
        Pedido.cpp
        Pedido.hpp
        utils.hpp
        PedidoEspecial.cpp
        PedidoEspecial.hpp
        PedidoUsual.cpp
        PedidoUsual.hpp
        PedidoEventual.cpp
        PedidoEventual.hpp
        Nodo.cpp
        Nodo.hpp
        Lista.cpp
        Lista.hpp
        Promociones.cpp
        Promociones.hpp)
