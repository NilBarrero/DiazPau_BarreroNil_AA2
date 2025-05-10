#pragma once
class CJ
{
public:
    int x;             // Current column on the map
    int y;             // Current row on the map
    char looking;      // Direction CJ is facing ('^', 'v', '<', '>')
    int money;         // CJ's current money
    int currentIsland; // Current island (0: Los Santos, 1: San Fierro, 2: Las Venturas)

    // Information from the configuration file (could be in another class or managed differently)
    int santosBridgeCost;    // Money needed to cross to San Fierro
    int maxSantosPedestrianMoney; // Maximum money from a pedestrian in Los Santos
    int fierroBridgeCost;   // Money needed to cross to Las Venturas
    int maxFierroPedestrianMoney;  // Maximum money from a pedestrian in San Fierro
};