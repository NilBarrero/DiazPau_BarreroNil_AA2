#include "map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

void initMap(Symbols& symbols, char** board, Mapa& mapa)
{
    mapa.gameState = 0;

    for (int i = 0; i < mapa.numRows; ++i)
    {
        for (int j = 0; j < mapa.numCols; ++j)
        {
            if (i == 0 || i == mapa.numRows / 2 || i == mapa.numRows - 1 || j == 0 || j == mapa.numCols / 2 || j == mapa.numCols - 1)
            {
                board[i][j] = symbols.wall;
            }
            else
            {
                board[i][j] = symbols.empty;
            }
        }

    }
}


