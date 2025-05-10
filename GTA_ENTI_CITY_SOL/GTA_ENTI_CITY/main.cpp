// Pokenti1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include "Mapa.h"
#include "CJ.h"
#include "Peaton.h"
#include <fstream>
#include <string>
#include <windows.h>

int main()
{
    Escena escenaActual = JUEGO; // Scene scene renombrado a Escena escenaActual
    bool juegoEnEjecucion = true; // bool gameState renombrado a bool juegoEnEjecucion
    DatosMapa datosMapa = { 0, 0, 5, 5 }; // Mapa mapa renombrado a DatosMapa datosMapa
    SimbolosMapa simbolosMapa = { '>', '<', '^', 'v', '-', 'P', 'X', '$' }; // Symbols symbols renombrado a SimbolosMapa simbolosMapa, 'O' a '$'
    CJ cj; // Ash ash renombrado a CJ cj
    datosMapa.interactuandoConPeaton = false; // mapa.interacionPokemon renombrado a datosMapa.interactuandoConPeaton

    // Abrir el archivo
    std::ifstream archivoConfiguracion("config.txt"); // archivo renombrado a archivoConfiguracion
    if (!archivoConfiguracion.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        //return 1;
    }
    char coma;
    archivoConfiguracion >> datosMapa.numFilasMapa >> coma; // mapa.numRows renombrado a datosMapa.numFilasMapa
    archivoConfiguracion >> datosMapa.numColumnasMapa >> coma; // mapa.numCols renombrado a datosMapa.numColumnasMapa
    archivoConfiguracion >> cj.costePuenteSantos >> coma; // ash.pokeInicial renombrado a cj.costePuenteSantos
    archivoConfiguracion >> cj.maxDineroPeatonSantos >> coma; // ash.pokeInicialRequeridos renombrado a cj.maxDineroPeatonSantos
    archivoConfiguracion >> cj.costePuenteFierro >> coma; // ash.pokeBosque renombrado a cj.costePuenteFierro
    archivoConfiguracion >> cj.maxDineroPeatonFierro >> coma; // ash.pokeBosqueRequeridos renombrado a cj.maxDineroPeatonFierro

    archivoConfiguracion.close();

    char** mapaJuego; // map renombrado a mapaJuego
    mapaJuego = new char* [datosMapa.numFilasMapa];

    for (int i = 0; i < datosMapa.numFilasMapa; i++)
    {
        mapaJuego[i] = new char[datosMapa.numColumnasMapa];
    }

    Peaton** peatones = new Peaton * [cj.costePuenteSantos + cj.costePuenteFierro]; // pokemones renombrado a peatones

    cj.dinero = 0; // ash.pokemonsCapturados renombrado a cj.dinero

    srand(time(NULL));
    inicializarMapa(simbolosMapa, mapaJuego, datosMapa, cj); // initializeMapa renombrado
    cj.posicionCJ = 0; // ash.positionAsh renombrado a cj.posicionCJ
    datosMapa.generarPeaton = true; // mapa.aparicionPokemon renombrado a datosMapa.generarPeaton

    while (juegoEnEjecucion == true) // gameState renombrado a juegoEnEjecucion
    {
        switch (escenaActual) // scene renombrado a escenaActual
        {
        case INICIO: // INIT

            //printTitle();
            Sleep(3000);
            std::system("cls");
            escenaActual = MENU; // scene renombrado a escenaActual
            break;

        case MENU: // MENU

            char entrada; // input renombrado a entrada

            std::cout << "Please enter 'P' to play or 'E' to exit: ";
            std::cin >> entrada;

            if (entrada == 'P' || entrada == 'p')
            {
                std::system("cls");
                escenaActual = JUEGO; // scene renombrado a escenaActual
            }
            else
            {
                std::system("cls");
                escenaActual = INICIO; // scene renombrado a escenaActual
                juegoEnEjecucion = false; // gameState renombrado a juegoEnEjecucion

            }

            break;

        case JUEGO: // GAME
            std::system("cls");
            imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); // printMapa renombrado

            if (datosMapa.numPeatonesSantos == 1) // mapa.pokemonsRequerios renombrado a datosMapa.numPeatonesSantos (asumiendo que se usa para contar algo)
            {
                if (datosMapa.escenaActual <= 3) // mapa.gameState renombrado a datosMapa.escenaActual
                {
                    datosMapa.escenaActual++; // mapa.gameState renombrado a datosMapa.escenaActual
                    datosMapa.generarPeaton = true; // mapa.aparicionPokemon renombrado a datosMapa.generarPeaton
                }
                datosMapa.numPeatonesSantos = 0; // mapa.pokemonsRequerios renombrado a datosMapa.numPeatonesSantos
            }


            if (mapaJuego[datosMapa.filaJugador - 1][datosMapa.columnaJugador] == simbolosMapa.peaton) { // map, mapa.p_row, mapa.p_col, symbols.pokemon renombrado
                datosMapa.interactuandoConPeaton = true; // mapa.interacionPokemon renombrado
                datosMapa.indicePeatonInteractuando = 1; // mapa.interacionPokemon2 renombrado
            }

            else if (mapaJuego[datosMapa.filaJugador + 1][datosMapa.columnaJugador] == simbolosMapa.peaton) { // map, mapa.p_row, mapa.p_col, symbols.pokemon renombrado
                datosMapa.interactuandoConPeaton = true; // mapa.interacionPokemon renombrado
                datosMapa.indicePeatonInteractuando = 2; // mapa.interacionPokemon2 renombrado
            }

            else if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador - 1] == simbolosMapa.peaton) { // map, mapa.p_row, mapa.p_col, symbols.pokemon renombrado
                datosMapa.interactuandoConPeaton = true; // mapa.interacionPokemon renombrado
                datosMapa.indicePeatonInteractuando = 3; // mapa.interacionPokemon2 renombrado
            }

            else if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador + 1] == simbolosMapa.peaton) { // map, mapa.p_row, mapa.p_col, symbols.pokemon renombrado
                datosMapa.interactuandoConPeaton = true; // mapa.interacionPokemon renombrado
                datosMapa.indicePeatonInteractuando = 4; // mapa.interacionPokemon2 renombrado
            }





            if (GetAsyncKeyState(VK_UP)) {
                if (mapaJuego[datosMapa.filaJugador - 1][datosMapa.columnaJugador] == simbolosMapa.vacio) { // map, mapa.p_row, mapa.p_col, symbols.empty renombrado
                    datosMapa.interactuandoConPeaton = false; // mapa.interacionPokemon renombrado
                    if (datosMapa.filaJugador - 1 < 5 || datosMapa.filaJugador - 1 > datosMapa.numFilasMapa - 7) { // mapa.p_row renombrado, mapa.numRows renombrado
                        datosMapa.filaJugador--; // mapa.p_row renombrado
                    }
                    else if (datosMapa.desplazamientoFilaMapa - 1 > -1) // mapa.m_row renombrado
                    {
                        datosMapa.desplazamientoFilaMapa--; // mapa.m_row renombrado
                        datosMapa.filaJugador--; // mapa.p_row renombrado
                    }
                }

                cj.posicionCJ = 1; // ash.positionAsh renombrado
                std::system("cls");
                imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); // printMapa renombrado
            }
            if (GetAsyncKeyState(VK_DOWN)) {
                if (mapaJuego[datosMapa.filaJugador + 1][datosMapa.columnaJugador] == simbolosMapa.vacio) { // map, mapa.p_row, mapa.p_col, symbols.empty renombrado
                    if (datosMapa.filaJugador + 1 < 6 || datosMapa.filaJugador + 1 > datosMapa.numFilasMapa - 6) // mapa.p_row renombrado, mapa.numRows renombrado
                    {
                        datosMapa.filaJugador++; // mapa.p_row renombrado
                    }
                    else if (datosMapa.desplazamientoFilaMapa + 1 < datosMapa.numFilasMapa + 1) // mapa.m_row renombrado, mapa.numRows renombrado
                    {
                        datosMapa.desplazamientoFilaMapa++; // mapa.m_row renombrado
                        datosMapa.filaJugador++; // mapa.p_row renombrado
                    }
                }

                cj.posicionCJ = 0; // ash.positionAsh renombrado
                std::system("cls");
                imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); // printMapa renombrado
            }
            if (GetAsyncKeyState(VK_LEFT)) {
                datosMapa.interactuandoConPeaton = false; // mapa.interacionPokemon renombrado
                if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador - 1] == simbolosMapa.vacio) { // map, mapa.p_row, mapa.p_col, symbols.empty renombrado
                    if (datosMapa.columnaJugador - 1 < 5) // mapa.p_col renombrado
                    {
                        datosMapa.columnaJugador--; // mapa.p_col renombrado
                    }
                    else if (datosMapa.desplazamientoColumnaMapa - 1 > -1) // mapa.m_col renombrado
                    {
                        datosMapa.desplazamientoColumnaMapa--; // mapa.m_col renombrado
                        datosMapa.columnaJugador--; // mapa.p_col renombrado
                    }
                }

                cj.posicionCJ = 3; // ash.positionAsh renombrado
                std::system("cls");
                imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); // printMapa renombrado
            }
            if (GetAsyncKeyState(VK_RIGHT)) {
                datosMapa.interactuandoConPeaton = false; // mapa.interacionPokemon renombrado
                if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador + 1] == simbolosMapa.vacio) { // map, mapa.p_row, mapa.p_col, symbols.empty renombrado
                    if (datosMapa.columnaJugador + 1 < 6) // mapa.p_col renombrado
                    {
                        datosMapa.columnaJugador++; // mapa.p_col renombrado
                    }
                    else if (datosMapa.desplazamientoColumnaMapa + 1 < datosMapa.numColumnasMapa + 1) // mapa.m_col renombrado, mapa.numCols renombrado
                    {
                        datosMapa.desplazamientoColumnaMapa++; // mapa.m_col renombrado
                        datosMapa.columnaJugador++; // mapa.p_col renombrado
                    }
                }
                cj.posicionCJ = 4; // ash.positionAsh renombrado
                std::system("cls");
                imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); // printMapa renombrado

            }
            if (GetAsyncKeyState(VK_SPACE)) {
                switch (cj.posicionCJ) // ash.positionAsh renombrado
                {
                case 0:
                    if (mapaJuego[datosMapa.filaJugador - 1][datosMapa.columnaJugador] == simbolosMapa.peaton) { // map, mapa.p_row, mapa.p_col, symbols.pokemon renombrado

                        mapaJuego[datosMapa.filaJugador - 1][datosMapa.columnaJugador] = simbolosMapa.vacio; // map, mapa.p_row, mapa.p_col, symbols.empty renombrado
                        datosMapa.numPeatonesSantos++; // mapa.pokemonsRequerios renombrado
                        cj.dinero++; // ash.pokemonsCapturados renombrado a cj.dinero
                        //InteraccionPokemon()
                        std::system("cls");
                        imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); // printMapa renombrado
                    }
                    break;
                case 1:
                    if (mapaJuego[datosMapa.filaJugador + 1][datosMapa.columnaJugador] == simbolosMapa.peaton) { // map, mapa.p_row, mapa.p_col, symbols.pokemon renombrado
                        mapaJuego[datosMapa.filaJugador + 1][datosMapa.columnaJugador] = simbolosMapa.vacio; // map, mapa.p_row, mapa.p_col, symbols.empty renombrado
                        datosMapa.numPeatonesSantos++; // mapa.pokemonsRequerios renombrado
                        cj.dinero++; // ash.pokemonsCapturados renombrado a cj.dinero
                        std::system("cls");
                        imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); // printMapa renombrado
                    }
                    break;
                case 2:
                    if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador - 1] == simbolosMapa.peaton) { // map, mapa.p_row, mapa.p_col, symbols.pokemon renombrado
                        mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador - 1] = simbolosMapa.vacio; // map, mapa.p_row, mapa.p_col, symbols.empty renombrado
                        datosMapa.numPeatonesSantos++; // mapa.pokemonsRequerios renombrado
                        cj.dinero++; // ash.pokemonsCapturados renombrado a cj.dinero
                        std::system("cls");
                        imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); // printMapa renombrado
                    }
                    break;
                case 3:
                    if (mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador + 1] == simbolosMapa.peaton) { // map, mapa.p_row, mapa.p_col, symbols.pokemon renombrado
                        mapaJuego[datosMapa.filaJugador][datosMapa.columnaJugador + 1] = simbolosMapa.vacio; // map, mapa.p_row, mapa.p_col, symbols.empty renombrado
                        datosMapa.numPeatonesSantos++; // mapa.pokemonsRequerios renombrado
                        cj.dinero++; // ash.pokemonsCapturados renombrado a cj.dinero
                        std::system("cls");
                        imprimirMapa(simbolosMapa, mapaJuego, datosMapa, cj, peatones); // printMapa renombrado
                    }
                    break;
                }
            }
            if (GetAsyncKeyState(VK_ESCAPE)) {
                escenaActual = FIN_PARTIDA; // scene renombrado a escenaActual, GAMEOVER renombrado
            }
            Sleep(200);
            break;
        case FIN_PARTIDA: // GAMEOVER renombrado a FIN_PARTIDA
            std::system("cls");
            //printGameOver();
            Sleep(5000);
            std::system("cls");
            escenaActual = MENU; // scene renombrado a escenaActual
            break;
        }
    }
}