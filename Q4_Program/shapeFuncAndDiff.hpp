#pragma once
#include <vector>
using namespace std;//使shapeFunc函数像全局变量一样，从而不被重载
vector<double> shapeFunc(double s, double t);//声明了指针函数shapeFunc,指针储存的是函数的首地址
vector<double> DiffShape(double s, double t);			//s,t是局部坐标


