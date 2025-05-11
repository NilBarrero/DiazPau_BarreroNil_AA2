#include <iostream>
#include "Mapa.h"
#include "CJ.h"
#include "Peaton.h"
#include <fstream>
#include <string>
#include <windows.h>

int main()
{
    Escena escenaActual = JUEGO; 
    bool juegoEnEjecucion = true; 
    DatosMapa datosMapa = { 0, 0, 5, 5 }; 
    SimbolosMapa simbolosMapa = { '>', '<', '^', 'v', '-', 'P', 'X', '$' }; 
    CJ cj; 
    datosMapa.interactuandoConPeaton = false; 

    // Abrir el archivo
    std::ifstream archivoConfiguracion("config.txt"); 
    if (!archivoConfiguracion.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        
    }
    char coma;
    archivoConfiguracion >> datosMapa.numFilasMapa >> coma; 
    archivoConfiguracion >> datosMapa.numColumnasMapa >> coma; 
    archivoConfiguracion >> cj.costePuenteSantos >> coma; 
    archivoConfiguracion >> cj.maxDineroPeatonSantos >> coma;
    archivoConfiguracion >> cj.costePuenteFierro >> coma; 
    archivoConfiguracion >> cj.maxDineroPeatonFierro >> coma; 

    archivoConfiguracion.close();

    char** mapaJuego; 
    mapaJuego = new char* [datosMapa.numFilasMapa];

    for (int i = 0; i < datosMapa.numFilasMapa; i++)
    {
        mapaJuego[i] = new char[datosMapa.numColumnasMapa];
    }

    Peaton** peatones = new Peaton * [cj.costePuenteSantos + cj.costePuenteFierro]; 

    cj.dinero = 0; 

    srand(time(NULL));
    inicializarMapa(simbolosMapa, mapaJuego, datosMapa, cj);
    cj.posicionCJ = 0; 
    datosMapa.generarPeaton = true; 

    while (juegoEnEjecucion == true) 
    {
        switch (escenaActual) 
        {
        case INICIO: 

            Sleep(3000);
            std::system("cls");
            escenaActual = MENU; 
            break;

        case MENU: 

            char entrada; 

            std::cout << "Please enter 'P' to play or 'E' to exit: ";
            std::cin >> entrada;

            if (entrada == 'P' || entrada == 'p')
            {
                std::system("cls");
                escenaActual = JUEGO; 
            }
            else
            {
                std::system("cls");
                escenaActual = INICIO; 
                juegoEnEjecucion = false; 

            }

            break;

        case JUEGO: 
            std::system("cls");
            // Agrega peatones vivos al mapa antes de imprimir
            for (int i = 0; i < datosMapa.numPeatonesSantos; ++i) {
                if (peatones[i]->estaVivo) {
                    mapaJuego[peatones[i]->fila][peatones[i]->columna] = 'P';
                }
            }

            imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); 

            if (datosMapa.numPeatonesSantos == 1) 
            {
                if (datosMapa.escenaActual <= 3) 
                {
                    datosMapa.escenaActual++; 
                    datosMapa.generarPeaton = true; 
                }
                datosMapa.numPeatonesSantos = 0; 
            }


            if (mapaJuego[datosMapa.filaJugador - 1][datosMapa.columnaJugador] == simbolosMapa.peaton) { 
                datosMapa.interactuandoConPeaton = true; 
                datosMapa.indicePeatonInteractuando = 1; 
            }

            else if (mapaJuego[datosMapa.filaJugador + 1][datosMapa.columnaJugador] == simbolosMapa.peaton) { 
                datosMapa.interactuandoConPeaton = true; 
                datosMapa.indicePeatonInteractuando = 2; 
            }

            else if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador - 1] == simbolosMapa.peaton) { 
                datosMapa.interactuandoConPeaton = true; 
                datosMapa.indicePeatonInteractuando = 3; 
            }

            else if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador + 1] == simbolosMapa.peaton) { 
                datosMapa.interactuandoConPeaton = true; 
                datosMapa.indicePeatonInteractuando = 4; 
            }





            if (GetAsyncKeyState(VK_UP)) {
                if (mapaJuego[datosMapa.filaJugador - 1][datosMapa.columnaJugador] == simbolosMapa.vacio) { 
                    datosMapa.interactuandoConPeaton = false; 
                    if (datosMapa.filaJugador - 1 < 5 || datosMapa.filaJugador - 1 > datosMapa.numFilasMapa - 7) { 
                        datosMapa.filaJugador--; 
                    }
                    else if (datosMapa.desplazamientoFilaMapa - 1 > -1) 
                    {
                        datosMapa.desplazamientoFilaMapa--; 
                        datosMapa.filaJugador--; 
                    }
                }

                cj.posicionCJ = 0; 
                std::system("cls");
                imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); 
            }
            if (GetAsyncKeyState(VK_DOWN)) {
                if (mapaJuego[datosMapa.filaJugador + 1][datosMapa.columnaJugador] == simbolosMapa.vacio) { 
                    if (datosMapa.filaJugador + 1 < 6 || datosMapa.filaJugador + 1 > datosMapa.numFilasMapa - 6) 
                    {
                        datosMapa.filaJugador++;
                    }
                    else if (datosMapa.desplazamientoFilaMapa + 1 < datosMapa.numFilasMapa + 1) 
                    {
                        datosMapa.desplazamientoFilaMapa++; 
                        datosMapa.filaJugador++;
                    }
                }

                cj.posicionCJ = 1; 
                std::system("cls");
                imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); 
            }
            if (GetAsyncKeyState(VK_LEFT)) {
                datosMapa.interactuandoConPeaton = false; 
                if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador - 1] == simbolosMapa.vacio) { 
                    if (datosMapa.columnaJugador - 1 < 5) 
                    {
                        datosMapa.columnaJugador--; 
                    }
                    else if (datosMapa.desplazamientoColumnaMapa - 1 > -1) 
                    {
                        datosMapa.desplazamientoColumnaMapa--; 
                        datosMapa.columnaJugador--; 
                    }
                }

                cj.posicionCJ = 2; 
                std::system("cls");
                imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); 
            }
            if (GetAsyncKeyState(VK_RIGHT)) {
                datosMapa.interactuandoConPeaton = false; 
                if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador + 1] == simbolosMapa.vacio) { 
                    if (datosMapa.columnaJugador + 1 < 6) 
                    {
                        datosMapa.columnaJugador++; 
                    }
                    else if (datosMapa.desplazamientoColumnaMapa + 1 < datosMapa.numColumnasMapa + 1) 
                    {
                        datosMapa.desplazamientoColumnaMapa++; 
                        datosMapa.columnaJugador++; 
                    }
                }
                cj.posicionCJ = 3; 
                std::system("cls");
                imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); 

            }
            if (GetAsyncKeyState(VK_SPACE)) {
                switch (cj.posicionCJ) 
                {
                case 0:
                    if (mapaJuego[datosMapa.filaJugador - 1][datosMapa.columnaJugador] == simbolosMapa.peaton) { 

                        mapaJuego[datosMapa.filaJugador - 1][datosMapa.columnaJugador] = simbolosMapa.vacio; 
                        datosMapa.numPeatonesSantos++; 
                        cj.dinero++; 
                        
                        std::system("cls");
                        imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); 
                    }
                    break;
                case 1:
                    if (mapaJuego[datosMapa.filaJugador + 1][datosMapa.columnaJugador] == simbolosMapa.peaton) { 
                        mapaJuego[datosMapa.filaJugador + 1][datosMapa.columnaJugador] = simbolosMapa.vacio; 
                        datosMapa.numPeatonesSantos++; 
                        cj.dinero++; 
                        std::system("cls");
                        imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); 
                    }
                    break;
                case 2:
                    if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador - 1] == simbolosMapa.peaton) { 
                        mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador - 1] = simbolosMapa.vacio; 
                        datosMapa.numPeatonesSantos++; 
                        cj.dinero++; 
                        std::system("cls");
                        imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); 
                    }
                    break;
                case 3:
                    if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador + 1] == simbolosMapa.peaton) { 
                        mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador + 1] = simbolosMapa.vacio; 
                        datosMapa.numPeatonesSantos++; 
                        cj.dinero++; 
                        std::system("cls");
                        imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); 
                    }
                    break;
                }
            }
            if (GetAsyncKeyState(VK_ESCAPE)) {
                escenaActual = FIN_PARTIDA; 
            }
            Sleep(200);
            break;
        case FIN_PARTIDA: 
            std::system("cls");
            Sleep(5000);
            std::system("cls");
            escenaActual = MENU; 
            break;
        }
    }
}