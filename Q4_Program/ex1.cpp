/*
		作者：Charlie_Xia
		功能：简单的有限元算例

*/

#include <iostream>
#include <vector>
#include "Elemstiffness.hpp"
#include "readData.hpp"
#include <cmath>
#include <numeric>
#include<math.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include<stdlib.h>
using namespace std;


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

	vector<double> b(2 * nodes.size(),0);
	vector<vector<double>> K(2 * nodes.size(),b);

	// 清空b vector 并且回收内存
	vector<double>().swap(b);

	// 初始化单元刚度矩阵
	for (int j = 0; j < 8; j++)
	{
		b.push_back(0);
	}
	vector<vector<double>>Ke(8,b);
	// 清空b vector 并且回收内存
	vector<double>().swap(b);
	
	for (int i = 0; i < sizeof(elements); i++)				//k个单元求k次单元刚度矩阵
	{
		// 求单元刚度矩阵
		Ke = ElementStiffness(30000000, 0.3, 1, nodes[elements[i][0] - 1][0], nodes[elements[i][0] - 1][1], 
			nodes[elements[i][1] - 1][0], nodes[elements[i][1] - 1][1], nodes[elements[i][2] - 1][0], 
			nodes[elements[i][2] - 1][1], nodes[elements[i][3] - 1][0], nodes[elements[i][3] - 1][1]);

		//整合到总体刚度矩阵中
		for (int j = 0; j < 4; j++)
		{
			for (int p = 0; p < 4; p++)
			{
				K[2 *  elements[i][j] - 2][2 * elements[i][p] - 2] = Ke[2 * j][2 * p] + K[2 * elements[i][j] - 2][2 * elements[i][p] - 2];
				K[2 * elements[i][j] - 2][2 * elements[i][p] - 2 + 1] = Ke[2 * j][2 * p + 1] + K[2 * elements[i][j] - 2][2 * elements[i][p] - 2 + 1];
				K[2 * elements[i][j] - 2 + 1][2 * elements[i][p] - 2] = Ke[2 * j + 1][2 * p] + K[2 * elements[i][j] - 2 + 1][2 * elements[i][p] - 2];
				K[2 * elements[i][j] - 2 + 1][2 * elements[i][p] - 2 + 1] = Ke[2 * j + 1][2 * p + 1] + K[2 * elements[i][j] - 2 + 1][2 * elements[i][p] - 2 + 1];
			}
		}
	}
	// 查看刚度矩阵实际容量大小与当前实际包含的元素个数
	cout << K.capacity() << " " <<K.size();
	
	/*
	//引入边界条件，利用对角元素改1法对对整体刚度矩阵K和载荷阵做修正
	for (int i = 0; i < sizeof(bounds); i++)
	{
		if (bounds[i][0] == 0)
			0;//不处理
		else
		{
			K[2 * i][2 * i] = 1;
			loads[i][0] = 0;
			for (int j = 0; j < 2 * i; j++)
				K[2 * i][j] = 0;
			for (int j = 2 * i + 1; j < 2 * sizeof(bounds); j++)
				K[2 * i][j] = 0;

			for (int j = 0; j < 2 * i; j++)
				K[j][2*i] = 0;
			for (int j = 2 * i + 1; j < 2 * sizeof(bounds); j++)
				K[j][2*i] = 0;
		}
		if (bounds[i][1] == 0)
			0;//不处理
		else	
		{
			K[2 * i + 1][2 * i + 1] = 1;
			loads[i][1] = 0;
			for (int j = 0; j < 2 * i + 1; j++)
				K[2 * i + 1][j] = 0;
			for (int j = 2 * i + 2; j < 2 * sizeof(bounds); j++)
				K[2 * i + 1][j] = 0;

			for (int j = 0; j < 2 * i + 1; j++)
				K[j][2 * i + 1] = 0;
			for (int j = 2 * i + 2; j < 2 * sizeof(bounds); j++)
				K[j][2 * i + 1] = 0;
		}

	}



	//解方程
	
	vector<int> F;
	
	for (int i = 0; i < 2 * sizeof(loads)-1; i=i+2)  //把二维向量loads转化为一维向量F，方便调用
	{
		F[i] = loads[i / 2][0];
		F[i+1]= loads[i / 2][1];
	}
	
	double x[2 * sizeof(nodes)][2 * sizeof(nodes)];
	for (int i = 0; i < 2 * sizeof(nodes); i++) 
		x[0][i]=0;
	
	double e;
	e = 0.02;
	void cau();
	{

		for (int k = 1; k <= 10; k++)
		{
			for (int i = 0; i < 2 * sizeof(nodes); i++)
			{
				x[k][i] = 1.0 / K[i][i];
				double re = F[i];
				for (int j = 0; j < 2 * sizeof(nodes); j++)
				{
					if (j != i)
						re -= K[i][j] * x[k - 1][j];
				}
				x[k][i] *= re;
			}
			for (int i = 0; i < 2 * sizeof(nodes); i++)
			{
				cout << x[k][i] << " ";
				cout << endl;
			}
			bool judge = true;
			for (int i = 0; i < 2 * sizeof(nodes); i++)
				if (fabs(x[k - 1][i] - x[k][i]) > e) {
					judge = false; break;
				}
			if (judge == true) return;

		}
	}
	*/


}







