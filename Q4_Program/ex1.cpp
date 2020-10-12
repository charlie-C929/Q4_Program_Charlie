/*
		作者：Charlie_Xia
		功能：简单的有限元算例

*/

#include <iostream>
#include "readData.hpp"
using namespace std;

int ex1()
{
	vector<vector<double>> nodes;			// 定义节点坐标数组
	nodes = readData_1();								// 读取节点坐标
	vector<vector<double>> loads;			// 定义载荷数组
	loads = readData_2();								// 
	vector<vector<double>> elements;		// 定义单元的节点编号
	elements = readData_3();						// 
	vector<vector<double>> bounds;			// 定义边界条件
	bounds = readData_3();							// 

	/*
			所有数据都读入了，接下来就该计算单元刚度矩阵，与组装刚度矩阵了
	*/








	return 0;
}



