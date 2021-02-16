#include "B_matrix.hpp"
#include "ja.hpp"
#include <malloc.h>
#include<vector>


vector<vector<double>> ElementStiffness(double E, double u, double h, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	//				单元刚度矩阵为8x8矩阵
	//				E ：弹性模量；u ：泊松比；h：厚度
	//				弹性矩阵 D

	double D[3][3] = { E / (1 - u * u) ,E * u / (1 - u * u) , 0, E * u / (1 - u * u) ,E / (1 - u * u) , 0, 0, 0,(1 - u) * E / (2 * (1 - u * u)) };


	//				初始化单元刚度矩阵

	vector<vector<double>> Ke;		//	创建一个二维向量
	vector<double> b;
	for (int j = 0; j < 8; j++)
	{
		b.push_back(0);
	}
	for (int i = 0; i < 8; i++)   //初始化
	{
		Ke.push_back(b);
	}

	//				高斯积分
	
	double x[2] = { -0.577350 , 0.577350 };	//假设需要两个高斯积分点，查询高斯积分表得到两个高斯点的函数值
	int W[2] = { 1,1 };			        	//高斯积分的权重


	double B[3][8], Bt[8][3];				//  定义几何矩阵及其转置
	double J[2][2];							//  定义雅可比矩阵
	double detJ = 0;
	double BtD[8][3];

	//				初始化BtD

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			BtD[i][j] = 0;
		}
	}

	//		对四个积分点进行高斯积分，求解单元刚度矩阵

	for (int a = 0; a < 2; a++)
	{
		for (int b = 0; b < 2; b++)
		{

			//				初始化BtD
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					BtD[i][j] = 0;
				}
			}

			//				求几何矩阵B及其转置矩阵
			vector<vector<double>> bmatrix = BMatrix(x1, y1, x2, y2, x3, y3, x4, y4, x[a], x[b]);
			for (int s = 0; s < 3; s++)
			{
				for (int k = 0; k < 8; k++)
				{
					B[s][k] = bmatrix[s][k];
				}
			}
			//	B 转置矩阵Bt

			for (int s = 0; s < 3; s++)
			{
				for (int k = 0; k < 8; k++)
				{

					Bt[k][s] = B[s][k];

				}
			}

			//			求雅可比矩阵 J	以及detJ
			vector<vector<double>>Ja = Jacobi(x1, y1, x2, y2, x3, y3, x4, y4, x[a], x[b]);
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					J[i][j] = Ja[i][j];
				}
			}
			detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];
			

			//			B的转置×D  BtD
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						BtD[i][j] = BtD[i][j] + Bt[i][k] * D[k][j];
					}
				}
			}
			//			求单元刚度矩阵
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						Ke[i][j] = Ke[i][j] + BtD[i][k] * B[k][j] * detJ * h * W[a] * W[b];

					}
				}
			}
		}
	}

	return Ke;

}