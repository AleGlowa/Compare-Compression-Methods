# **Compare-Compression-Methods**
The traineeship project to rank three compression methods (A, B, C) by generating reports in form of text files and plots.

## **General info**
I'm adding it to my portfolio because it links C++ and Python together and that it's been written mostly in C++.

## **Input of the program**
There are three files, each describe compressed point cloud with 2109 points obtained by three different compress methods. All are unordered.
In order to compare compression methods, these points must be ordered according to uncompressed point cloud described in Car_XYZI_uncompressed_ASCII.ply file.
Car_uncompressed.png file charts these uncompressed point cloud.

## **Output of the program**
Program saves:
- Aordered.txt, Bordered.txt, Cordered.txt - ordered cloud points for each method
- Ametrics.txt, Bmetrics.txt, Cmetrics.txt - metrics for each method. GeoAvg( average difference in distance ), GeoMax( maximum distance ),
AvgAbsDiffReflectivity( average absolute difference in reflectivity )
- methodsRanking.txt - from most accurate method to the least
- point_vs_distance.pdf - plot which charts differences in distance and their mean
- point_vs_r_diff.pdf - plot which charts differences in reflectivity and their mean

## **Technologies**
- C++11
- CMake 3.10.0
- Python 3
- Matplotlib 3.1.1

## **Requirements**
- Bash
- gcc/g++
- CMake

## **How to build and execute?**
`./run.sh`

## **Features**
Ready features:
- saving reports in form of text files
- saving reports in form of plots as pdf files

To-do list( from the most important ):
- optimize an algorithm for ordering points from brute force O(n^2) to O(n*log(n)) using the divide and conquere method.

## **Status**
Project is: in progress

## **Contact**
My email: alglowa1@gmail.com  
Linkedin: [Alex Głowacki](https://www.linkedin.com/in/alex-g%C5%82owacki-72941113a/)
