// Mapa.cpp
#include "Mapa.h"
#include "CJ.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib> // Para rand()

void inicializarMapa(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, CJ cj)
{
    datosMapa.escenaActual = 0;

    for (int i = 0; i < datosMapa.numFilasMapa; ++i)
    {
        for (int j = 0; j < datosMapa.numColumnasMapa; ++j)
        {
            if (i == 0 || i == datosMapa.numFilasMapa / 3 || i == 2 * datosMapa.numFilasMapa / 3 || i == datosMapa.numFilasMapa - 1 ||
                j == 0 || j == datosMapa.numColumnasMapa / 2 || j == datosMapa.numColumnasMapa - 1)
            {
                mapaJuego[i][j] = simbolos.pared;
            }
            else
            {
                mapaJuego[i][j] = simbolos.vacio;
            }
        }
    }
    datosMapa.filaJugador = 1; // Inicializar la posición del jugador
    datosMapa.columnaJugador = 1;
}

void imprimirMapa(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, CJ cj, Peaton** peatones)
{
    actualizarMapa(simbolos, mapaJuego, datosMapa, cj, peatones);
    for (int i = datosMapa.desplazamientoFilaMapa; i < NUM_ROWS_VISIBLE + datosMapa.desplazamientoFilaMapa; ++i)
    {
        for (int j = datosMapa.desplazamientoColumnaMapa; j < NUM_COLUMNS_VISIBLE + datosMapa.desplazamientoColumnaMapa; ++j)
        {
            if (i == datosMapa.filaJugador && j == datosMapa.columnaJugador)
            {
                switch (cj.posicionCJ)
                {
                case 0: // Arriba
                    std::cout << simbolos.cjArriba << " ";
                    break;
                case 1: // Abajo
                    std::cout << simbolos.cjAbajo << " ";
                    break;
                case 2: // Izquierda
                    std::cout << simbolos.cjIzquierda << " ";
                    break;
                case 3: // Derecha
                    std::cout << simbolos.cjDerecha << " ";
                    break;
                default:
                    std::cout << "? ";
                    break;
                }
            }
            else if (i >= 0 && i < datosMapa.numFilasMapa && j >= 0 && j < datosMapa.numColumnasMapa)
            {
                switch (mapaJuego[i][j])
                {
                case 'X':
                    std::cout << simbolos.pared << " ";
                    break;
                case '-':
                    std::cout << simbolos.vacio << " ";
                    break;
                case 'P':
                    std::cout << simbolos.peaton << " ";
                    break;
                case '$':
                    std::cout << simbolos.dinero << " ";
                    break;
                default:
                    std::cout << mapaJuego[i][j] << " ";
                    break;
                }
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Dinero: " << cj.dinero << std::endl;
    if (datosMapa.interactuandoConPeaton == true)
    {
        std::cout << "Hablando con alguien..." << std::endl;
        // Aquí iría la lógica de la interacción
        // con el peatón identificado por datosMapa.indicePeatonInteractuando
    }
}

void actualizarMapa(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, CJ& cj, Peaton** peatones)
{
    datosMapa.desplazamientoFilaMapa = datosMapa.filaJugador - NUM_ROWS_VISIBLE / 2;
    datosMapa.desplazamientoColumnaMapa = datosMapa.columnaJugador - NUM_ROWS_VISIBLE / 2;

    if (datosMapa.desplazamientoFilaMapa < 0) datosMapa.desplazamientoFilaMapa = 0;
    if (datosMapa.desplazamientoColumnaMapa < 0) datosMapa.desplazamientoColumnaMapa = 0;
    if (datosMapa.desplazamientoFilaMapa > datosMapa.numFilasMapa - NUM_ROWS_VISIBLE) datosMapa.desplazamientoFilaMapa = datosMapa.numFilasMapa - NUM_ROWS_VISIBLE;
    if (datosMapa.desplazamientoColumnaMapa > datosMapa.numColumnasMapa - NUM_ROWS_VISIBLE) datosMapa.desplazamientoColumnaMapa = datosMapa.numColumnasMapa - NUM_ROWS_VISIBLE;
}

void generarDinero(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, int fila, int columna)
{
    if (fila >= 0 && fila < datosMapa.numFilasMapa && columna >= 0 && columna < datosMapa.numColumnasMapa && mapaJuego[fila][columna] == simbolos.vacio)
    {
        mapaJuego[fila][columna] = simbolos.dinero;
    }
}