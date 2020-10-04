/*

	程序作者：Max_Zhang
	输入：局部坐标 s，t
	输出：形函数或者形函数的导数
	
	主要功能：计算Q4单元的形函数及其导数

*/

#include<iostream>
using namespace std;

double* shapeFunc(double s, double t)
{
	double N[4];
	N[0] = (1 - s) * (1 - t) / 4;
	N[1] = (1 + s) * (1 - t) / 4;
	N[2] = (1 - s) * (1 + t) / 4;
	N[3] = (1 + s) * (1 + t) / 4;

	return N; // 返回的是形函数数组的头指针
}

double* DiffShape(double s, double t)			//s,t是局部坐标
{
	double Ns[8];			//		static

	Ns[0] = -(1 - t) / 4;	//  N1对s求导
	Ns[1] = (1 - t) / 4;	//  N2对s求导
	Ns[2] = (1 + t) / 4;	//  N3对s求导
	Ns[3] = -(1 + t) / 4;	//  N4对s求导
	Ns[4] = -(1 - s) / 4;	//	N1对t求导
	Ns[5] = -(1 + s) / 4;	//	N2对t求导
	Ns[6] = (1 + s) / 4;	//	N3对t求导
	Ns[7] = (1 - s) / 4;	//	N4对t求导

	return Ns;
}