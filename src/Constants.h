#pragma once
#ifndef __Constants__
#define __Constants__

// #include "raylib.h"
// #include "raymath.h"
#include <iostream>

enum Direction { NONE, NORTH, SOUTH, EAST, WEST };

inline Direction stringToDirection(const std::string& str) {
    if (str == "NORTH") {
        return NORTH;
    } else if (str == "EAST") {
        return EAST;
    } else if (str == "SOUTH") {
        return SOUTH;
    } else if (str == "WEST") {
        return WEST;
    } else {
        // Handle unknown direction or return a default value
        std::cerr << "Unknown direction: " << str << std::endl;
        return NORTH; // Or return a default direction
    }
}

namespace Constants
{
    const int cellSize = 64;
    const int cellCount = 15;
}

typedef enum
{
    RayLib_FLIP_NONE = 0x00000000,     /**< Do not flip */
    RayLib_FLIP_HORIZONTAL = 0x00000001,    /**< flip horizontally */
    RayLib_FLIP_VERTICAL = 0x00000002     /**< flip vertically */
} RayLib_FLIP;

#endif // __Constants__