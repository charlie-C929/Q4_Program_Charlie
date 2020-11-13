/*

	�������ߣ�Max_Zhang
	���룺
	�����
	��Ҫ���ܣ�����Q4��Ԫ���κ������䵼��

*/

#include<iostream>
#include<vector>
#include "shapeFuncAndDiff.hpp"
using namespace std;

vector<double> shapeFunc(double s, double t)//
{
	vector<double> N;
	for (int i = 0; i < 4; i++)//��ʼ��
	{
		N.push_back(0);
	}
	N[0] = (1 - s) * (1 - t) / 4;
	N[1] = (1 + s) * (1 - t) / 4;
	N[2] = (1 - s) * (1 + t) / 4;
	N[3] = (1 + s) * (1 + t) / 4;

	return N;
}

vector<double> DiffShape(double s, double t)			//s,t�Ǿֲ�����
{
    vector<double> Ns;			
	for (int i = 0; i < 8; i++)//��ʼ��
	{
		Ns.push_back(0);
	}
	Ns[0] = -(1 - t) / 4;	//  N1��s��
	Ns[1] = (1 - t) / 4;	//  N2��s��
	Ns[2] = (1 + t) / 4;	//  N3��s��
	Ns[3] = -(1 + t) / 4;	//  N4��s��
	Ns[4] = -(1 - s) / 4;	//	N1��t��
	Ns[5] = -(1 + s) / 4;	//	N2��t��
	Ns[6] = (1 + s) / 4;	//	N3��t��
	Ns[7] = (1 - s) / 4;	//	N4��t��

	return Ns;
}