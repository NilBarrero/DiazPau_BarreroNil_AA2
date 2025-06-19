#pragma once

class CJ
{
public:
    int x = 1, y = 1;          // Posici�n en el mapa
    char icono = 'v';          // Representaci�n

    int posicionCJ = 1;        // 0: arriba, 1: abajo, etc.
    int dinero = 0;
    int islaActual = 0;
    int salud = 100;

    // Coche
    bool enCoche = false;
    int cocheX = -1;
    int cocheY = -1;

    // Informaci�n del archivo de configuraci�n
    int costePuenteSantos = 500;
    int maxDineroPeatonSantos = 100;
    int costePuenteFierro = 1000;
    int maxDineroPeatonFierro = 150;
};
