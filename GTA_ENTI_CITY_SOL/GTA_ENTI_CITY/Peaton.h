// Peaton.h
#pragma once
#include <iostream>
#include <string>
#include <cstdlib> // Para funciones rand()
#include <ctime>    // Para función time()

class Peaton {
public:
    int fila; // posX renombrado a fila
    int columna; // posY renombrado a columna
    bool estaVivo; // Nuevo atributo para indicar si el peaton está disponible

    // Constructor
    Peaton(int fila, int columna)
        : fila(fila), columna(columna), estaVivo(true) {}

    // Podríamos añadir métodos específicos de los peatones si fuera necesario en el futuro
    // Ejemplo:
    // void interactuar();
};