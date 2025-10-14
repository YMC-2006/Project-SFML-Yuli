#pragma once
struct LevelConfig {
    int levelNumber;          // Actual Level
    int moves;                // Cantidad de movimientos
    int targetScore;          // Puntos que hay que alcanzar
    int gemTaskAmount;          // Cantidad de gemas que tengo que alcanzar
    int gemTask;             // El tipo de la gema morada, amarilla, etc...
    bool hasIceBlocks;        // Si tiene obstáculos o no
    bool enableBombGems;      // Si permite gemas bomba
};
