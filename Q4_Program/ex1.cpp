/*
		作者：Charlie_Xia
		功能：简单的有限元算例

*/

#include <iostream>
#include <vector>
#include "Elemstiffness.hpp"
#include "readData.hpp"
#include"B_matrix.hpp"
#include <cmath>
#include <numeric>
#include<math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include<stdlib.h>
#include<Eigen\Dense>
using namespace std;
using namespace Eigen;


void ex1()
{
	vector<vector<double>> nodes;			// 定义节点坐标数组
	nodes = readData_1();					// 读取节点坐标
	vector<vector<double>> loads;			// 定义载荷数组
	loads = readData_2();					// 
	vector<vector<int>> elements;		// 定义单元的节点编号
	elements = readData_3();				// 
	vector<vector<double>> bounds;			// 定义边界条件
	bounds = readData_4();					// 

	//		根据节点数定义总体刚度矩阵
	//		初始化总体刚度矩阵

	vector<double> b(2 * nodes.size(), 0);
	vector<vector<double>> K(2 * nodes.size(), b);

	// 清空b vector 并且回收内存
	vector<double>().swap(b);

	// 初始化单元刚度矩阵
	for (int j = 0; j < 8; j++)
	{
		b.push_back(0);
	}
	vector<vector<double>>Ke(8, b);
	// 清空b vector 并且回收内存
	vector<double>().swap(b);

	for (int i = 0; i < elements.size(); i++)				//k个单元求k次单元刚度矩阵
	{

		Ke = ElementStiffness(166667, 0.3, 1, nodes[elements[i][0] - 1][0], nodes[elements[i][0] - 1][1],
			nodes[elements[i][1] - 1][0], nodes[elements[i][1] - 1][1], nodes[elements[i][2] - 1][0],
			nodes[elements[i][2] - 1][1], nodes[elements[i][3] - 1][0], nodes[elements[i][3] - 1][1]);

		//整合到总体刚度矩阵中
		for (int j = 0; j < 4; j++)
		{
			for (int p = 0; p < 4; p++)
			{
				K[2 * elements[i][j] - 2][2 * elements[i][p] - 2] = Ke[2 * j][2 * p] + K[2 * elements[i][j] - 2][2 * elements[i][p] - 2];
				K[2 * elements[i][j] - 2][2 * elements[i][p] - 2 + 1] = Ke[2 * j][2 * p + 1] + K[2 * elements[i][j] - 2][2 * elements[i][p] - 2 + 1];
				K[2 * elements[i][j] - 2 + 1][2 * elements[i][p] - 2] = Ke[2 * j + 1][2 * p] + K[2 * elements[i][j] - 2 + 1][2 * elements[i][p] - 2];
				K[2 * elements[i][j] - 2 + 1][2 * elements[i][p] - 2 + 1] = Ke[2 * j + 1][2 * p + 1] + K[2 * elements[i][j] - 2 + 1][2 * elements[i][p] - 2 + 1];
			}
		}
	}




//引入边界条件，利用对角元素改1法对对整体刚度矩阵K和载荷阵做修正
	for (int i = 0; i < bounds.size(); i++)
	{
		if (bounds[i][0] == 0)
			;//不处理
		else
		{
			K[2 * i][2 * i] = 1;
			loads[i][0] = 0;
			// 一整行置0
			for (int j = 0; j < 2 * i; j++)
				K[2 * i][j] = 0;
			for (int j = 2 * i + 1; j < 2 * bounds.size(); j++)
				K[2 * i][j] = 0;

			for (int j = 0; j < 2 * i; j++)
				K[j][2 * i] = 0;
			for (int j = 2 * i + 1; j < 2 * bounds.size(); j++)
				K[j][2 * i] = 0;
		}
		if (bounds[i][1] == 0)
			;//不处理
		else
		{
			K[2 * i + 1][2 * i + 1] = 1;
			loads[i][1] = 0;
			for (int j = 0; j < 2 * i + 1; j++)
				K[2 * i + 1][j] = 0;
			for (int j = 2 * i + 2; j < 2 * bounds.size(); j++)
				K[2 * i + 1][j] = 0;

			for (int j = 0; j < 2 * i + 1; j++)
				K[j][2 * i + 1] = 0;
			for (int j = 2 * i + 2; j < 2 * bounds.size(); j++)
				K[j][2 * i + 1] = 0;
		}

	}

 // //测试
	//for (int i = 0; i < 2 * nodes.size(); i++)
	//{
	//	for (int j = 0; j < 2 * nodes.size(); j++)
	//	{
	//		cout << K[i][j] << "   "  ;
	//	}
	//	cout<<endl;
	//}






	vector<double> F(2 * nodes.size(), 0);

	for (int i = 0; i < nodes.size(); i++)    //把两列化为一列
	{
		F[2 * i] = loads[i][0];
		F[2 * i + 1] = loads[i][1];
		
	}
	


	//用eigen求解方程
	 MatrixXd Kmatrix(2 * nodes.size(), 2 * nodes.size());
	 VectorXd Fmatrix(2 * nodes.size());

	for (int j = 0; j < 2 * nodes.size(); j++)//共2 * sizeof(nodes)行
	{
		for (int i = 0; i < 2 * nodes.size(); i++)//共2 * sizeof(nodes)列 组成一行
		{
			Kmatrix(j,i) = K[j][i];
		}
	}

	for (int i = 0; i < 2 * nodes.size(); i++)//共2 * sizeof(nodes)列 组成一行
	{
		Fmatrix(i) = F[i];
	}

	// QR 分解求出位移向量x
	VectorXd x = Kmatrix.colPivHouseholderQr().solve(Fmatrix);




	//把位移向量化为n乘2的矩阵，方便输出
	vector<double> s(2, 0);
	vector<vector<double>> X(nodes.size(), s);
	// 清空s vector 并且回收内存
	vector<double>().swap(s);
	for (int i = 0; i < 2 * nodes.size(); i = i + 2)    //把一列化为两列
	{
		X[i / 2][0] = x(i);
		X[i / 2][1] = x(i + 1);
	}



	//测试
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i][0] << "  " << nodes[i][1] << "  " << X[i][0] << "   " << X[i][1] << endl;
	}



	//求出应力
	vector<double> stress_x(nodes.size(), 0);
	vector<double> stress_y(nodes.size(), 0);
	vector<double> stress_xy(nodes.size(), 0);

	double E = 166667, u = 0.3;
	double D[3][3] = { E / (1 - u * u) ,E * u / (1 - u * u) , 0, E * u / (1 - u * u) ,E / (1 - u * u) , 0, 0, 0,(1 - u) * E / (2 * (1 - u * u)) };
	double f[2] = { -0.577350 , 0.577350 };	//假设需要两个高斯积分点，查询高斯积分表得到两个高斯点的函数值
	for (int i = 0; i < elements.size(); i++)
	{
		vector<vector<double>> bmatrix = BMatrix(nodes[elements[i][0]-1][0], nodes[elements[i][0]-1][1] , nodes[elements[i][1]-1][0], nodes[elements[i][1]-1][1], nodes[elements[i][2]-1][0], nodes[elements[i][2]-1][1], nodes[elements[i][3]-1][0], nodes[elements[i][3]-1][1], f[0], f[1]);
		for (int j = 0; j < 4; j++)
		{
			double BX[3];
			BX[0] = bmatrix[0][2 * j] * X[elements[i][j] - 1][0] + bmatrix[0][2 * j + 1] * X[elements[i][j] - 1][1];
			BX[1]= bmatrix[1][2 * j] * X[elements[i][j] - 1][0] + bmatrix[1][2 * j + 1] * X[elements[i][j] - 1][1];
			BX[2]=bmatrix[2][2 * j] * X[elements[i][j] - 1][0] + bmatrix[2][2 * j + 1] * X[elements[i][j] - 1][1];
			stress_x[elements[i][j] - 1] = D[0][0] * BX[0] + D[0][1] * BX[1] + D[0][2] * BX[2];
			stress_y[elements[i][j] - 1] = D[1][0] * BX[0] + D[1][1] * BX[1] + D[1][2] * BX[2];
			stress_xy[elements[i][j] - 1] = D[2][0] * BX[0] + D[2][1] * BX[1] + D[2][2] * BX[2];
		}

	}

	






	

	//输出结果
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i][0] << "  " << nodes[i][1] << "  " << X[i][0] << "   " << X[i][1] << "  " << stress_x[i] << "   " << stress_y[i] << "  " << stress_xy[i] << endl;
	}
	
	
	}











