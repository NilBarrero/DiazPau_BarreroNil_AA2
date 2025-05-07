#pragma once
#include <iostream>
#include <string>
#include <cstdlib> // Para funciones rand()
#include <ctime>   // Para función time()

class Peaton {
public:
    int vida;
    int posX;
    int posY;

    // Constructor
    Peaton(int vida, int posX, int posY)
        : vida(vida), posX(posX), posY(posY) {}

};