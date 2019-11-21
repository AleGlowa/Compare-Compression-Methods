#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Constants connected with files' properties */

#include <string>

namespace Constants {
    const std::string inputPath{ "./input" };
    const std::string uncompressedCarName{ "Car_XYZI_uncompressed_ASCII.ply" };
    const std::string decompressedCarNames[]{
        "Car_XYZI_decompressed_ASCII_A.ply",
        "Car_XYZI_decompressed_ASCII_B.ply",
        "Car_XYZI_decompressed_ASCII_C.ply"
    };

    constexpr int elementVertex{ 2109 };                   // Number of points
    constexpr int readOffset{ 32 };                        // Number of lines which describe properties
    constexpr int numLines{ elementVertex + readOffset };
}

#endif