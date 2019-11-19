#ifndef POINTUTILS_H
#define POINTUTILS_H

#include <fstream>
#include <limits>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

#include "Point3D_64.h"
#include "constants.h"

using COLUMN_MAP = std::unordered_map< std::string, std::vector<double> >;
using VECTOR_PAIR = std::pair< std::vector<Point3D_64>, std::vector<Point3D_64> >;
class PointUtils {
private:
    static COLUMN_MAP s_columnMap;
    static void setMapValues(const std::string &sourceCarPath, const std::string &compareCarPath);
    static VECTOR_PAIR getPointsFromMap();

public:
    static void orderPoints(const std::string &sourceCarPath, const std::string &compareCarPath);
    static double averageGeoAcc(std::vector<double> &dists);
    inline static double maxGeoAcc(std::vector<double> &dists) { *std::max_element(dists.begin(), dists.end()); };
    static double avgReflectivityDiff(std::vector<double> &r_diffs);
};

#endif