// Mapa.h
#pragma once
#include "Peaton.h"
#include "CJ.h"
// La parte del mapa que se imprime
#define NUM_ROWS_VISIBLE 11
#define NUM_COLUMNS_VISIBLE 11

struct DatosMapa
{
    int desplazamientoFilaMapa; // Posicion del Mapa (desplazamiento vertical)
    int desplazamientoColumnaMapa; // Posicion del Mapa (desplazamiento horizontal)
    int filaJugador; // Posicion del Jugador (fila)
    int columnaJugador; // Posicion del Jugador (columna)

    // Fichero de configuración
    int numFilasMapa;
    int numColumnasMapa;

    int escenaActual;
    bool generarPeaton;

    // Interacción
    int numPeatonesSantos; 

    bool interactuandoConPeaton;
    int indicePeatonInteractuando; 
};

struct SimbolosMapa
{
    char cjDerecha; 
    char cjIzquierda; 
    char cjArriba; 
    char cjAbajo; 
    char vacio; 
    char peaton; 
    char pared; 
    char dinero; 
};

enum Escena { INICIO, MENU, JUEGO, FIN_PARTIDA };
void inicializarMapa(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, CJ cj);
void imprimirMapa(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, CJ cj, Peaton** peatones);
void actualizarMapa(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, CJ& cj, Peaton** peatones);
void generarDinero(SimbolosMapa& simbolos, char** mapaJuego, DatosMapa& datosMapa, int fila, int columna); 