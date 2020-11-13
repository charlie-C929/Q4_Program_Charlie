#include "shapeFuncAndDiff.hpp"
#include "ja.hpp"
#include <stdlib.h>
#include<vector>

using namespace std;

vector<vector<double>> BMatrix(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double s, double t)
{
		
	vector<double> Ns = DiffShape(s, t);
	vector<vector<double>> J= Jacobi(x1, y1, x2, y2, x3, y3, x4, y4, s, t);
	

	//			求雅可比矩阵行列式

	double detJ = 0;
	detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];
	



	//		初始化几何矩阵
	
	vector<double> b(8,0);
	vector<vector<double>> B(3,b);
	

	//		求几何矩阵
	//		B为3x8矩阵

	B[0][0] = (J[1][1] * Ns[0] - J[0][1] * Ns[4]) / detJ;
	B[0][2] = (J[1][1] * Ns[1] - J[0][1] * Ns[5]) / detJ;
	B[0][4] = (J[1][1] * Ns[2] - J[0][1] * Ns[6]) / detJ;
	B[0][6] = (J[1][1] * Ns[3] - J[0][1] * Ns[7]) / detJ;
	B[1][1] = (-J[1][0] * Ns[0] + J[0][0] * Ns[4]) / detJ;
	B[1][3] = (-J[1][0] * Ns[1] + J[0][0] * Ns[5]) / detJ;
	B[1][5] = (-J[1][0] * Ns[2] + J[0][0] * Ns[6]) / detJ;
	B[1][7] = (-J[1][0] * Ns[3] + J[0][0] * Ns[7]) / detJ;

	for (int i = 0; i < 8; i = i + 2)
	{
		B[2][i] = B[1][i + 1];
		B[2][i + 1] = B[0][i];
	}
	return B;
}