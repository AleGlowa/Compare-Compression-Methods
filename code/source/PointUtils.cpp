#include "PointUtils.h"

COLUMN_MAP PointUtils::s_columnMap;

void PointUtils::setMapValues(const std::string &sourceCarPath, const std::string &compareCarPath) {
    
    std::ifstream uncompressedCar{ sourceCarPath };
    if (!uncompressedCar) {
        std::cerr << sourceCarPath << " could not be opened for reading!\n";
        return;
    }

    std::vector<double> x_uncompressed, y_uncompressed, z_uncompressed, r_uncompressed;
    for (int iUncompLine = 1; iUncompLine < Constants::numLines; ++iUncompLine) {
        if (iUncompLine >= Constants::readOffset) {
            double uncompReadX, uncompReadY, uncompReadZ, uncompReadR;
            uncompressedCar >> uncompReadX >> uncompReadY >> uncompReadZ >> uncompReadR;
            x_uncompressed.push_back(uncompReadX);
            y_uncompressed.push_back(uncompReadY);
            z_uncompressed.push_back(uncompReadZ);
            r_uncompressed.push_back(uncompReadR);
        } else {
            std::string uncompLine;
            std::getline(uncompressedCar, uncompLine);
        }
    }
    s_columnMap["x_uncompressed"] = x_uncompressed;
    s_columnMap["y_uncompressed"] = y_uncompressed;
    s_columnMap["z_uncompressed"] = z_uncompressed;
    s_columnMap["r_uncompressed"] = r_uncompressed;
    uncompressedCar.close();

    std::ifstream decompressedCar{ compareCarPath };
    if (!decompressedCar) {
        std::cerr << compareCarPath << " could not be opened for reading!\n";
        return;
    }

    std::vector<double> x_decompressed, y_decompressed, z_decompressed, r_decompressed;
    for (int iDecompLine = 1; iDecompLine < Constants::numLines; ++iDecompLine) {
        if (iDecompLine >= Constants::readOffset) {
            double decompReadX, decompReadY, decompReadZ, decompReadR;
            decompressedCar >> decompReadX >> decompReadY >> decompReadZ >> decompReadR;
            x_decompressed.push_back(decompReadX);
            y_decompressed.push_back(decompReadY);
            z_decompressed.push_back(decompReadZ);
            r_decompressed.push_back(decompReadR);
        } else {
            std::string decompLine;
            std::getline(decompressedCar, decompLine);
        }
    }
    s_columnMap["x_decompressed"] = x_decompressed;
    s_columnMap["y_decompressed"] = y_decompressed;
    s_columnMap["z_decompressed"] = z_decompressed;
    s_columnMap["r_decompressed"] = r_decompressed;
    decompressedCar.close();
}

VECTOR_PAIR PointUtils::getPointsFromMap() {
    std::vector<Point3D_64> uncompPoints, decompPoints;
    std::size_t numRows{ s_columnMap["x_decompressed"].size() };
    
    for (std::size_t irow = 0; irow < numRows; ++irow) {
        std::vector<double> temp;
        for (const auto &column : s_columnMap) {
            temp.push_back(column.second[irow]);
        }
        Point3D_64 uncompPoint{ std::make_tuple(temp[4], temp[2], temp[5]), temp[6] };
        uncompPoints.push_back(uncompPoint);
        Point3D_64 decompPoint{ std::make_tuple(temp[3], temp[7], temp[1]), temp[0] };
        decompPoints.push_back(decompPoint);
    }

    return std::make_pair(uncompPoints, decompPoints);
}

void PointUtils::orderPoints(const std::string &sourceCarPath, const std::string &compareCarPath) {

    // get map values
    PointUtils::setMapValues(sourceCarPath, compareCarPath);
    // create points from map
    std::vector<Point3D_64> uncompPoints, decompPoints;
    std::tie(uncompPoints, decompPoints) = PointUtils::getPointsFromMap();

    // Brute force method
    std::vector<double> minDists, reflectivityDiffs;
    for (const auto &uncompPoint : uncompPoints) {

        double minDist{ std::numeric_limits<double>::max() };   // Initialize minDist with max possible double value
        Point3D_64 nearestDecompPoint;
        for (const auto &decompPoint : decompPoints) {
            double dist{ uncompPoint.euclideanDistance(decompPoint) };
            if (dist < minDist) {
                minDist = dist;
                nearestDecompPoint = decompPoint;
            }
        }
        double reflectivityDiff{ uncompPoint.reflectivityDiff(nearestDecompPoint) };
        minDists.push_back(minDist);
        reflectivityDiffs.push_back(reflectivityDiff);

        // save this line to file
        std::cout << uncompPoint << " " << nearestDecompPoint << " " << minDist << " " << reflectivityDiff << std::endl;
    }

    s_columnMap["distance"] = minDists;
    s_columnMap["r_diff"] = reflectivityDiffs;
    
}

double PointUtils::averageGeoAcc(std::vector<double> &dists) {
    std::size_t size{ dists.size() };
    double sum{ std::accumulate(dists.begin(), dists.end(), 0.0) };

    return sum / size;
}

double PointUtils::avgReflectivityDiff(std::vector<double> &r_diffs) {
    std::size_t size{ r_diffs.size() };
    double sum{ std::accumulate(r_diffs.begin(), r_diffs.end(), 0.0) };

    return sum / size;
}