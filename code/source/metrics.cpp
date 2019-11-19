#include <iostream>
#include <iomanip>

#include "PointUtils.h"


int main() {

    // Save into output file float numbers without a scientific notation
    // and with 10 points after decimal point
    std::cout << std::fixed << std::setprecision(10);

    int numColumns = 10;
    int distanceColumn = 9, rDiffColumn = 10;
    std::vector<double> dists, r_diffs;
    for (int line = 1; line <= Constants::elementVertex; ++line) {
        for (int column = 1; column <= numColumns; ++column) {
            double number;
            std::cin >> number;
            if (column == distanceColumn)
                dists.push_back(number);
            else if (column == rDiffColumn) {
                r_diffs.push_back(number);
            }
        }
    }

    std::cout << "GeoAvg = " << PointUtils::averageGeoAcc(dists)
              << "\tGeoMax = " << PointUtils::maxGeoAcc(dists)
              << "\tAvgAbsDiffReflectivity = " << PointUtils::avgReflectivityDiff(r_diffs) << std::endl;

    return 0;
}