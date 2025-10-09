#pragma once
struct LevelConfig {
    int levelNumber;          // Actual Level
    int moves;                // Cantidad de movimientos
    int targetScore;          // Puntos que hay que alcanzar
    int gemTaskAmount;
    int gemTask;           
    bool hasIceBlocks;        // Si tiene obstáculos o no
    bool enableBombGems;      // Si permite gemas bomba
     // Para cambiar el fondo dependiendo del nivel
};
