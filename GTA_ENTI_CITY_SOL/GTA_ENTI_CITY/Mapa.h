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




/*
#include "Pedestrian.h"

void Pedestrian::Move(const Map& map, int px, int py)
{
    if (!alive) return;

    // Si está cerca del CJ no se mueve
    if (abs(x - px) <= 1 && abs(y - py) <= 1) return;

    int nx = x + (horitzontal ? (rand() % 3 - 1) : 0);
    int ny = y + (!horitzontal ? (rand() % 3 - 1) : 0);

    if (map.CanPass(nx, ny))
    {
        x = nx;
        y = ny;
    }
}

void Pedestrian::PassiveOrAgressive()
{
    passive = rand() % 2;
}

void Pedestrian::Hurt()
{
    hits--;
    if (hits <= 0)
        alive = false;
}

void Pedestrian::SetAgressive()
{
    passive = false;
}

void Pedestrian::InmuneToRunOver()
{
    inmuneRunOver = true;
}

bool Pedestrian::GetInmuneToRunOver()
{
    return inmuneRunOver;
}


#pragma once
#include "Map.h"
#include <cstdlib>
#include <ctime>

struct Pedestrian
{
    int hits = 2;
    int x, y;
    bool alive = true;
    bool horitzontal = true;
    int island;
    bool passive;
    bool attackingCJ = false;
    bool inmuneRunOver = false;
    clock_t lastAttackTime = 0;

    void Move(const Map& map, int px, int py);

    void PassiveOrAgressive();
    void SetAgressive();
    void InmuneToRunOver();
    bool GetInmuneToRunOver();

    void Hurt();
};
*/

class Map
{
private:
    char** grid;
    int width, height;

public:
    Map(int w, int h);
    ~Map();

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    char Get(int x, int y) const;
    void Set(int x, int y, char symbol);
    void Clear(int x, int y);
    bool CanPass(int x, int y) const;

    void DrawWalls();
    void PrintView(int cx, int cy, char symbol, int viewX, int viewY);
};