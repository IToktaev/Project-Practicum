#pragma once
#include <stdint.h>

const char EMPTY_TILE = '0';
const char SOLID_TILE = '1';

enum class TileType : uint8_t {
    Empty = 0,
    Solid = 1
};