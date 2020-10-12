//计算雅克比矩阵
#include <iostream>
#include "shapeFuncAndDiff.hpp"
using namespace std;
double** Jacobi(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double s, double t)
{
	//		单元坐标
	double X[4] = { x1,x2,x3,x4 };
	double Y[4] = { y1,y2,y3,y4 };
	static double** J;					//		static
	//		求形函数的导数

	double Ns[8];


	for (int i = 0; i < 8; i++)
	{
		Ns[i] = *(DiffShape(s, t) + i);
		//cout << Ns[i]<<"  ";			//测试
	}

	//		初始化雅可比矩阵
	J = (double**)malloc(2 * sizeof(double));
	for (int i = 0; i < 2; i++)
	{
		J[i] = (double*)malloc(2 * sizeof(double));
		for (int j = 0; j < 2; j++)
		{
			J[i][j] = 0;
		}

	}

	//求雅可比矩阵
	double J1 = 0, J2 = 0, J3 = 0, J4 = 0;



	for (int i = 0; i < 4; i++)
	{
		J1 = J1 + Ns[i] * X[i];
		J2 = J2 + Ns[i] * Y[i];
		J3 = J3 + Ns[i + 4] * X[i];
		J4 = J4 + Ns[i + 4] * Y[i];
	}

	J[0][0] = J1;
	J[0][1] = J2;
	J[1][0] = J3;
	J[1][1] = J4;

	//	cout << (J1*J4 - J2 *J3) << endl;
	return J;
}








