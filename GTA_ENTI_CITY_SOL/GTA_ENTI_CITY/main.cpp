// GTA_ENTI_CITY.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

int main()
{
    Mapa map;
    // Abrir el archivo
    std::ifstream configFile("config.txt");
    if (!configFile.is_open()) {
        std::cout << "File not found" << std::endl;
    }
    char comma;
    configFile >> map.numRows >> comma;
    configFile >> map.numCols >> comma;
    configFile >> map.initialNPC1 >> comma;
    configFile >> map.neededNPC1 >> comma;
    configFile >> map.maxLoot1 >> comma;
    configFile >> map.initialNPC2 >> comma;
    configFile >> map.neededNPC2 >> comma;
    configFile >> map.maxLoot2 >> comma;

    configFile.close();
    std::cout << map.numRows << std::endl;
    std::cout << map.numCols << std::endl;
    std::cout << map.initialNPC1 << std::endl;
    std::cout << map.neededNPC1 << std::endl;
    std::cout << map.maxLoot1 << std::endl;
    std::cout << map.initialNPC2 << std::endl;
    std::cout << map.neededNPC2 << std::endl;
    std::cout << map.maxLoot2 << std::endl;
}

