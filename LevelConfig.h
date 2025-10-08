#pragma once
struct LevelConfig {
    int levelNumber;          // Actual Level
    int moves;                // Cantidad de movimientos
    int targetScore;          // Puntos que hay que alcanzar
    int typeGem; //**
    int gemTask;           // Cantidad de gemas rojas que hay que eliminar
    bool hasIceBlocks;        // Si tiene obstáculos o no
    bool enableBombGems;      // Si permite gemas bomba
     // Para cambiar el fondo dependiendo del nivel
};
