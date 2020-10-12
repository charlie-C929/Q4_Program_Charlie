#include <iostream>
#include "shapeFuncAndDiff.hpp"
#include "Ja.hpp"
using namespace std;
//double eleB(double J[2][2], double Ns[8])
//{
//	double B[2][8];
//	//B[0][0] = (J[1][1] * Ns[0] - J[0][1] * Ns[4]) / detJ;
//	//B[0][2] = (J[1][1] * Ns[1] - J[0][1] * Ns[5]) / detJ;
//	//B[0][4] = (J[1][1] * Ns[2] - J[0][1] * Ns[6]) / detJ;
//	//B[0][6] = (J[1][1] * Ns[3] - J[0][1] * Ns[7]) / detJ;
//	//B[1][1] = (-J[1][0] * Ns[0] + J[0][0] * Ns[4]) / detJ;
//	//B[1][3] = (-J[1][0] * Ns[1] + J[0][0] * Ns[5]) / detJ;
//	//B[1][5] = (-J[1][0] * Ns[2] + J[0][0] * Ns[6]) / detJ;
//	//B[1][7] = (-J[1][0] * Ns[3] + J[0][0] * Ns[7]) / detJ;
//
//	for (int i = 0; i < 8; i = i + 2)
//	{
//		B[2][i] = B[1][i + 1];
//		B[2][i + 1] = B[0][i];
//	}
//	/*return B;*/
//}