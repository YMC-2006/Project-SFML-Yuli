#pragma once
struct LevelConfig {
    int levelNumber;          // Actual Level
    int moves;                // Movements per levels
    int targetScore;          // Points to reach
    int gemTaskAmount;        // Amount of gems to get in order to win
    int gemTask;              // the gem type
    bool hasIceBlocks;        // if it has obstacles or not
    bool enableBombGems;      // if allows bomb gems
    bool isUnlocked;          // if the levels is yet to unlock  
    bool swapBooster;         // the swap booster that is only available on lvl 5

};
