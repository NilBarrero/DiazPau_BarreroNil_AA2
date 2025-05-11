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
    bool estaVivo; 

    // Constructor
    Peaton(int fila, int columna)
        : fila(fila), columna(columna), estaVivo(true) {}

    
};