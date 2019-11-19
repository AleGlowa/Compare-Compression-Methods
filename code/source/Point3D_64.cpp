#include "Point3D_64.h"

// operators overloading
std::ostream& operator<<(std::ostream &out, const Point3D_64 &point) {
    out << std::get<0>(point.m_coords) << " " << std::get<1>(point.m_coords) << " " << std::get<2>(point.m_coords) << " " << point.m_reflectivity;
    return out;
}

// methods
double Point3D_64::euclideanDistance(const Point3D_64 &point) const {
    double x{ std::get<0>(m_coords) - std::get<0>(point.m_coords) };
    double y{ std::get<1>(m_coords) - std::get<1>(point.m_coords) };
    double z{ std::get<2>(m_coords) - std::get<2>(point.m_coords) };

    double dist{ std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2)) };

    return dist;
}