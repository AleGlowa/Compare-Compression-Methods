#include <iostream>
#include <iomanip>
#include <string>

#include "PointUtils.h"


int main(int argc, const char **argv) {
    
    if (argc != 2) {
        std::cerr << "You entered wrong number of arguments! As an argument pass only a filename\n";
        return -1;
    }
    const std::string fileName{ std::string(argv[1]) };

    // Save into output file float numbers without a scientific notation
    // and with 10 points after decimal point
    std::cout << std::fixed << std::setprecision(10);

    std::string uncompPath{ Constants::inputPath + "/" +  Constants::uncompressedCarName };

    // order points
    std::string decompPath{ Constants::inputPath + "/" + fileName };
    PointUtils::orderPoints(uncompPath, decompPath);

    return 0;
}