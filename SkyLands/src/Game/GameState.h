#pragma once
#include <cstdint>

enum GameState : uint8_t {
    homeState,
    levelState,
    menuState,
    victoryState,
    defeatState
};