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

void colocarPeatones(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, Peaton** peatones)
{
    for (int i = 0; i < datosMapa.numPeatonesSantos; ++i)
    {
        if (peatones[i]->estaVivo)
        {
            int f = peatones[i]->fila;
            int c = peatones[i]->columna;
            if (mapaJuego[f][c] == simbolos.vacio)
            {
                mapaJuego[f][c] = simbolos.peaton;
            }
        }
    }
}


void imprimirMapa(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, CJ cj, Peaton** peatones)
{
    actualizarMapa(simbolos, mapaJuego, datosMapa, cj, peatones);
    colocarPeatones(simbolos, mapaJuego, datosMapa, peatones);

    for (int i = datosMapa.desplazamientoFilaMapa; i < NUM_ROWS_VISIBLE + datosMapa.desplazamientoFilaMapa; ++i)
    {
        for (int j = datosMapa.desplazamientoColumnaMapa; j < NUM_COLUMNS_VISIBLE + datosMapa.desplazamientoColumnaMapa; ++j)
        {
            if (i == datosMapa.filaJugador && j == datosMapa.columnaJugador)
            {
                switch (cj.posicionCJ)
                {
                case 0: std::cout << simbolos.cjArriba << " "; break;
                case 1: std::cout << simbolos.cjAbajo << " "; break;
                case 2: std::cout << simbolos.cjIzquierda << " "; break;
                case 3: std::cout << simbolos.cjDerecha << " "; break;
                default: std::cout << "? "; break;
                }
            }
            else if (i >= 0 && i < datosMapa.numFilasMapa && j >= 0 && j < datosMapa.numColumnasMapa)
            {
                switch (mapaJuego[i][j])
                {
                case 'X': std::cout << simbolos.pared << " "; break;
                case '-': std::cout << simbolos.vacio << " "; break;
                case 'P': std::cout << simbolos.peaton << " "; break;
                case '$': std::cout << simbolos.dinero << " "; break;
                default: std::cout << mapaJuego[i][j] << " "; break;
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
    if (datosMapa.interactuandoConPeaton)
    {
        std::cout << "Hablando con alguien..." << std::endl; //test
    }
}


void actualizarMapa(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, CJ& cj, Peaton** peatones)
{
    datosMapa.desplazamientoFilaMapa = datosMapa.filaJugador - NUM_ROWS_VISIBLE / 2;
    datosMapa.desplazamientoColumnaMapa = datosMapa.columnaJugador - NUM_COLUMNS_VISIBLE / 2;

    if (datosMapa.desplazamientoFilaMapa < 0) datosMapa.desplazamientoFilaMapa = 0;
    if (datosMapa.desplazamientoColumnaMapa < 0) datosMapa.desplazamientoColumnaMapa = 0;
    if (datosMapa.desplazamientoFilaMapa > datosMapa.numFilasMapa - NUM_ROWS_VISIBLE) datosMapa.desplazamientoFilaMapa = datosMapa.numFilasMapa - NUM_ROWS_VISIBLE;
    if (datosMapa.desplazamientoColumnaMapa > datosMapa.numColumnasMapa - NUM_COLUMNS_VISIBLE) datosMapa.desplazamientoColumnaMapa = datosMapa.numColumnasMapa - NUM_COLUMNS_VISIBLE;

    // Insertar peatones en el mapa
    for (int i = 0; i < datosMapa.numPeatonesSantos; ++i)
    {
        if (peatones[i]->estaVivo)
        {
            int f = peatones[i]->fila;
            int c = peatones[i]->columna;
            if (mapaJuego[f][c] == simbolos.vacio) {
                mapaJuego[f][c] = simbolos.peaton;
            }
        }
    }
}

void generarDinero(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, int fila, int columna)
{
    if (fila >= 0 && fila < datosMapa.numFilasMapa && columna >= 0 && columna < datosMapa.numColumnasMapa && mapaJuego[fila][columna] == simbolos.vacio)
    {
        mapaJuego[fila][columna] = simbolos.dinero;
    }
}


//#include "Map.h"
/*

Map::Map(int w, int h) : width(w), height(h)
{
    grid = new char* [height];
    for (int i = 0; i < height; i++)
    {
        grid[i] = new char[width];
        for (int j = 0; j < width; j++)
        {
            grid[i][j] = '.';
        }
    }

    for (int y = 0; y < height; y++)
    {
        if (y != height / 2)
        {
            grid[y][width / 3] = 'X';
            grid[y][2 * width / 3] = 'X';
        }
    }
}

Map::~Map()
{
    for (int i = 0; i < height; i++)
        delete[] grid[i];
    delete[] grid;
}

char Map::Get(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return grid[y][x];
    return ' ';
}

void Map::Set(int x, int y, char symbol)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        grid[y][x] = symbol;
}

void Map::Clear(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        grid[y][x] = '.';
}

bool Map::CanPass(int x, int y) const
{
    char tile = Get(x, y);
    return tile == '.' || tile == '$' || tile == 'T';
}

void Map::DrawWalls()
{
    for (int y = 0; y < height; y++)
    {
        if (y != height / 2)
            grid[y][width / 3] = 'X';
        else
            grid[y][width / 3] = 'T';

        if (y != height / 2)
            grid[y][2 * width / 3] = 'X';
        else
            grid[y][2 * width / 3] = 'T';
    }
}

void Map::PrintView(int cx, int cy, char symbol, int viewX, int viewY)
{
    system("cls");
    for (int dy = -viewY / 2; dy <= viewY / 2; dy++)
    {
        for (int dx = -viewX / 2; dx <= viewX / 2; dx++)
        {
            int x = cx + dx;
            int y = cy + dy;

            if (x == cx && y == cy)
                std::cout << symbol;
            else
                std::cout << Get(x, y);
        }
        std::cout << std::endl;
    }
}
*/

