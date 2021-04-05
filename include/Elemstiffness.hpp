#ifndef ELEMSTIFFNESS_HPP
#define ELEMSTIFFNESS_HPP
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "shapeFuncAndDiff.hpp"
vector<vector<double>> ElementStiffness(double E, double u, double h, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
//用于计算单元刚度矩阵
#endif