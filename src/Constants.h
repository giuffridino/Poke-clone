#pragma once
#ifndef __Constants__
#define __Constants__

// #include "raylib.h"
// #include "raymath.h"
#include <iostream>

enum Direction { NONE, NORTH, SOUTH, EAST, WEST };

inline Color textColor = Color{119, 117, 118, 255};
inline Color textColor2 = Color{90, 82, 82, 255};


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
    const int windowWidth = 1200;
    const int windowHeight = 800;
}

typedef enum
{
    RayLib_FLIP_NONE = 0x00000000,     /**< Do not flip */
    RayLib_FLIP_HORIZONTAL = 0x00000001,    /**< flip horizontally */
    RayLib_FLIP_VERTICAL = 0x00000002     /**< flip vertically */
} RayLib_FLIP;

inline std::string replaceWithNewLineChar(std::string string, int &numNewLines)
{
    size_t found = string.find("\\n");
    // std::cout << found << "\n";
    while (found != std::string::npos) {
        string.replace(found, 2, "\n");
        found = string.find("\\n", found + 1);
        numNewLines++;
    }
    return string;
}

#endif // __Constants__