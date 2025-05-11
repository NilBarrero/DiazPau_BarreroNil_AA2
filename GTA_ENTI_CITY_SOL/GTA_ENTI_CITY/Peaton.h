// Peaton.h
#pragma once
#include <iostream>
#include <string>
#include <cstdlib> // Para funciones rand()
#include <ctime>    // Para función time()

class Peaton {
public:
    int fila; 
    int columna; 
    bool estaVivo; // Nuevo atributo para indicar si el peaton está disponible

    // Constructor
    Peaton(int fila, int columna)
        : fila(fila), columna(columna), estaVivo(true) {}

    
};