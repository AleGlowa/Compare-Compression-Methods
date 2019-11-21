#ifndef POINT3D_64_H
#define POINT3D_64_H

#include <tuple>
#include <iostream>
#include <cmath>

class PointUtils;

// make it more readable, create alias for tuple with 3 values
using Tuple3D_64 = std::tuple<double, double, double>;
class Point3D_64 {
private:
    Tuple3D_64 m_coords;
    double m_reflectivity;

public:
    // Constructors
    Point3D_64() : m_coords{ std::make_tuple(0.0, 0.0, 0.0) }, m_reflectivity{ 0.0 } { }
    Point3D_64(Tuple3D_64 coords, double reflectivity) : m_coords{ coords }, m_reflectivity{ reflectivity } { }
    
    // operators overloading
    friend std::ostream& operator<<(std::ostream &out, const Point3D_64 &point);
    
    // getters
    double getReflectivity() const { return m_reflectivity; }
    Tuple3D_64 getCoords() const { return m_coords; }

    // setters
    void setReflectivity(double reflectivity) { m_reflectivity = reflectivity; }
    void setCoords(Tuple3D_64 coords) { m_coords = coords; }

    // methods
    double euclideanDistance(const Point3D_64 &point) const; // Calculate an euclidean distance
    inline double reflectivityDiff(const Point3D_64 &point) const { return std::abs(m_reflectivity - point.m_reflectivity); }

};

/* Point3D_64 Class */

#endif