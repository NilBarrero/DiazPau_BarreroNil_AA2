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

using namespace std;

const int VISTA_ANCHO = 20;  // tamaño visible del mapa horizontal
const int VISTA_ALTO = 10;   // tamaño visible del mapa vertical

struct CJ {
    int x = 0, y = 0;
    char icono = 'v';
};

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

int main() {
    srand(time(0));

    int ancho, alto, p1, d1, m1, d2, m2;
    tie(ancho, alto, p1, d1, m1, d2, m2) = leerConfig();

    vector<vector<char>> mapa(alto, vector<char>(ancho, '#'));

    CJ cj;
    cj.x = 1;
    cj.y = 1;
    mapa[cj.y][cj.x] = cj.icono;

    // Crear peatones aleatorios para Los Santos
    vector<Peaton> peatones;
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

    while (true) {
        mostrarVista(mapa, cj);
        if (GetAsyncKeyState(VK_ESCAPE)) break;

        // Mover CJ
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

        moverPeatones(peatones, mapa, cj);

        Sleep(100);
    }

    return 0;
}
