/*

	程序作者：Max_Zhang
	输入：
	输出：
	主要功能：计算Q4单元的形函数及其导数

*/

#include<iostream>
#include<vector>
#include "shapeFuncAndDiff.hpp"
using namespace std;

vector<double> shapeFunc(double s, double t)//
{
	vector<double> N;
	for (int i = 0; i < 4; i++)//初始化
	{
		N.push_back(0);
	}
	N[0] = (1 - s) * (1 - t) / 4;
	N[1] = (1 + s) * (1 - t) / 4;
	N[2] = (1 - s) * (1 + t) / 4;
	N[3] = (1 + s) * (1 + t) / 4;

	return N;
}

vector<double> DiffShape(double s, double t)			//s,t是局部坐标
{
    vector<double> Ns;			
	for (int i = 0; i < 8; i++)//初始化
	{
		Ns.push_back(0);
	}
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