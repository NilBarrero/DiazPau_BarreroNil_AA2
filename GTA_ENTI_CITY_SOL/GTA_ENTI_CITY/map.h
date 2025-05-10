#pragma once

#define NUM_ROWS_PRINT 11
#define NUM_COLUMNS_PRINT 11

struct Mapa
{
    int mapRows; //map position
    int mapCols;
    int playerRow; //Posicion del Player
    int playerCol;

    //file
    int numRows;
    int numCols;

    int initialNPC1;
    int neededNPC1;
    int maxLoot1;

    int initialNPC2;
    int neededNPC2;
    int maxLoot2;

    int gameState;
};

struct Symbols
{
    char p_right;
    char p_left;
    char p_up;
    char p_down;
    char empty;
    char wall;
    
};

enum Scene { INIT, MENU, GAME, GAMEOVER };

void initMap(Symbols& symbols, char** board, Mapa& mapa); // <--- AQUI VA EL CJ
/*
void printMapa(Symbols& symbols, char** board, Mapa& mapa, -> AQUI VA EL CJ <- );
void actualizarMapa(Symbols& symbols, char** board, Mapa& mapa, -> AQUI VA EL CJ <- );
*/