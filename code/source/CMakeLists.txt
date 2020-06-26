cmake_minimum_required(VERSION 3.10.0)
project(Compare-Compression-Methods)

set(ORDER_SOURCES constants.h Point3D_64.h Point3D_64.cpp PointUtils.h PointUtils.cpp)
set(METRIC_SOURCES ${ORDER_SOURCES})

add_executable(orderPoints orderPoints.cpp ${ORDER_SOURCES})

add_executable(metrics metrics.cpp ${METRIC_SOURCES})