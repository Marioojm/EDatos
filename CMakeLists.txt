cmake_minimum_required(VERSION 3.27)
project(practica_4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(practica_4
        Avl.h
        Farmacia.cpp
        Farmacia.h
        Laboratorios.cpp
        Laboratorios.h
        listasEnlazadas.h
        main.cpp
        MediExpress.cpp
        MediExpress.h
        PaMedicamentos.cpp
        PaMedicamentos.h
        Stock.cpp
        Stock.h
        VecDin.h)
