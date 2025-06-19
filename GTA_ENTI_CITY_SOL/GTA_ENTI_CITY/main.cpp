//main.cpp
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <random>
#include "CJ.h"

using namespace std;

const int VISTA_ANCHO = 20;  // tamaño visible del mapa horizontal
const int VISTA_ALTO = 10;   // tamaño visible del mapa vertical

struct Peaton {
    int x = 0, y = 0;
    bool horizontal = true;
};

// Leer configuración
std::tuple<int, int, int, int, int, int, int> leerConfig() {
    ifstream file("config.txt");
    int ancho, alto;
    int p1, d1, m1;
    int p2, d2, m2;
    char sep;
    file >> ancho >> sep >> alto >> sep;
    file >> p1 >> sep >> d1 >> sep >> m1 >> sep;
    file >> p2 >> sep >> d2 >> sep >> m2;
    return { ancho, alto, p1, d1, m1, d2, m2 };
}

// Mostrar vista centrada en CJ
void mostrarVista(const vector<vector<char>>& mapa, CJ& cj) {
    system("cls");
    int inicioY = max(0, cj.y - VISTA_ALTO / 2);
    int finY = min((int)mapa.size(), inicioY + VISTA_ALTO);
    int inicioX = max(0, cj.x - VISTA_ANCHO / 2);
    int finX = min((int)mapa[0].size(), inicioX + VISTA_ANCHO);

    for (int i = inicioY; i < finY; ++i) {
        for (int j = inicioX; j < finX; ++j) {
            cout << mapa[i][j];
        }
        cout << endl;
    }
}

// Mover peatones
void moverPeatones(vector<Peaton>& peatones, vector<vector<char>>& mapa, CJ& cj) {
    for (auto& p : peatones) {
        // Si CJ está a 1 casilla, se detiene
        if (abs(p.x - cj.x) <= 1 && abs(p.y - cj.y) <= 1) continue;

        mapa[p.y][p.x] = '#';
        if (p.horizontal) {
            int dir = rand() % 2 ? 1 : -1;
            if (p.x + dir > 0 && p.x + dir < mapa[0].size() && mapa[p.y][p.x + dir] == '#')
                p.x += dir;
        }
        else {
            int dir = rand() % 2 ? 1 : -1;
            if (p.y + dir > 0 && p.y + dir < mapa.size() && mapa[p.y + dir][p.x] == '#')
                p.y += dir;
        }
        mapa[p.y][p.x] = 'P';
    }
}

const int INIT = 0;
const int MENU = 1;
const int GAME = 2;
const int GAMEOVER = 3;
const int EXIT = 4;

int main() {
    srand(time(0));
    int estado = INIT;
    DWORD tiempoInicio;
    bool bigSmokeDerrotado = false;
    bool sinDinero = false;
    bool cruzandoPeaje = false;
    bool sinVida = false;
    bool ePresionada = false;

    CJ cj;
    vector<Peaton> peatones;
    vector<vector<char>> mapa;
    int ancho, alto, p1, d1, m1, d2, m2;

    while (estado != EXIT) {
        switch (estado) {
        case INIT: {
            system("cls");
            cout << "====== GRAND CJ AUTO ======" << endl;
            cout << "Cargando..." << endl;
            Sleep(3000);  // Espera 3 segundos
            estado = MENU;
            break;
        }

        case MENU: {
            system("cls");
            cout << "====== MENU PRINCIPAL ======" << endl;
            cout << "1. Play" << endl;
            cout << "2. Exit" << endl;

            while (true) {
                if (_kbhit()) {
                    char opcion = _getch();
                    if (opcion == '1') {
                        estado = GAME;
                        break;
                    }
                    else if (opcion == '2') {
                        estado = EXIT;
                        break;
                    }
                }
            }
            break;
        }

        case GAME: {
            tie(ancho, alto, p1, d1, m1, d2, m2) = leerConfig();
            mapa.assign(alto, vector<char>(ancho, '#'));
            peatones.clear();
            cj.x = 1;
            cj.y = 1;
            cj.icono = 'v';
            mapa[cj.y][cj.x] = cj.icono;

            // Spawnear coche cerca de CJ (solo para testeo
            int cocheSpawnX = cj.x + 1;
            int cocheSpawnY = cj.y + 1;

            if (mapa[cocheSpawnY][cocheSpawnX] == '#') {
                mapa[cocheSpawnY][cocheSpawnX] = 'C';
            }
            //---------------------------------------------
            for (int i = 0; i < p1; ++i) {
                Peaton p;
                p.x = rand() % ancho;
                p.y = rand() % (alto / 3);
                p.horizontal = rand() % 2;
                if (mapa[p.y][p.x] == '#') {
                    mapa[p.y][p.x] = 'P';
                    peatones.push_back(p);
                }
            }

            // Variables de juego
            int dinero = 10;
            int salud = 10;

            while (true) {
                mostrarVista(mapa, cj);
                if (GetAsyncKeyState(VK_ESCAPE)) {
                    estado = MENU;
                    break;
                }

                // Simulación simple para condiciones de GameOver:
                if (cj.y == alto - 1) {
                    cruzandoPeaje = true;
                    if (dinero <= 0) {
                        sinDinero = true;
                    }
                }

                if (salud <= 0) sinVida = true;

                // Condiciones de GameOver
                if (bigSmokeDerrotado || (cruzandoPeaje && sinDinero) || sinVida) {
                    estado = GAMEOVER;
                    tiempoInicio = GetTickCount();
                    break;
                }

                //Subir a coche
                if (GetAsyncKeyState('E') & 0x8000) {
                    if (!ePresionada) {
                        if (!cj.enCoche) {
                            // Ver si hay un coche adyacente
                            bool subido = false;
                            for (int dx = -1; dx <= 1 && !subido; ++dx) {
                                for (int dy = -1; dy <= 1 && !subido; ++dy) {
                                    int nx = cj.x + dx;
                                    int ny = cj.y + dy;
                                    if (nx >= 0 && ny >= 0 && nx < ancho && ny < alto && mapa[ny][nx] == 'C') {
                                        cj.enCoche = true;
                                        cj.cocheX = nx;
                                        cj.cocheY = ny;
                                        mapa[cj.y][cj.x] = '#'; // CJ desaparece
                                        subido = true;
                                    }
                                }
                            }
                        }
                        else {
                            // Bajar del coche
                            bool bajado = false;
                            for (int dx = -1; dx <= 1 && !bajado; ++dx) {
                                for (int dy = -1; dy <= 1 && !bajado; ++dy) {
                                    int nx = cj.cocheX + dx;
                                    int ny = cj.cocheY + dy;
                                    if (nx >= 0 && ny >= 0 && nx < ancho && ny < alto && mapa[ny][nx] == '#') {
                                        cj.enCoche = false;
                                        cj.x = nx;
                                        cj.y = ny;
                                        mapa[ny][nx] = cj.icono;
                                        bajado = true;
                                    }
                                }
                            }
                        }
                        ePresionada = true;
                    }
                }
                else {
                    ePresionada = false;
                }

                // Movimiento (CJ o coche)
                if (!cj.enCoche) {
                    mapa[cj.y][cj.x] = '#';
                    if (GetAsyncKeyState(VK_UP) && cj.y > 0) {
                        cj.y--;
                        cj.icono = '^';
                    }
                    else if (GetAsyncKeyState(VK_DOWN) && cj.y < alto - 1) {
                        cj.y++;
                        cj.icono = 'v';
                    }
                    else if (GetAsyncKeyState(VK_LEFT) && cj.x > 0) {
                        cj.x--;
                        cj.icono = '<';
                    }
                    else if (GetAsyncKeyState(VK_RIGHT) && cj.x < ancho - 1) {
                        cj.x++;
                        cj.icono = '>';
                    }
                    mapa[cj.y][cj.x] = cj.icono;
                }
                else {
                    mapa[cj.cocheY][cj.cocheX] = '#';
                    if (GetAsyncKeyState(VK_UP) && cj.cocheY > 0) {
                        cj.cocheY--;
                    }
                    else if (GetAsyncKeyState(VK_DOWN) && cj.cocheY < alto - 1) {
                        cj.cocheY++;
                    }
                    else if (GetAsyncKeyState(VK_LEFT) && cj.cocheX > 0) {
                        cj.cocheX--;
                    }
                    else if (GetAsyncKeyState(VK_RIGHT) && cj.cocheX < ancho - 1) {
                        cj.cocheX++;
                    }
                    mapa[cj.cocheY][cj.cocheX] = 'C';
                }

                moverPeatones(peatones, mapa, cj);

                // Simula pérdida de salud para pruebas
                //salud--;

                Sleep(100);
            }
            break;
        }

        case GAMEOVER: {
            system("cls");
            cout << "===== GAME OVER =====" << endl;
            if (bigSmokeDerrotado) cout << "Derrotaste a Big Smoke!" << endl;
            else if (sinVida) cout << "Te has quedado sin salud." << endl;
            else if (sinDinero && cruzandoPeaje) cout << "No tenías dinero para el peaje y fuiste detenido." << endl;
            else cout << "Motivo desconocido." << endl;

            Sleep(5000);
            estado = EXIT;
            break;
        }
        }
    }

    return 0;
}

