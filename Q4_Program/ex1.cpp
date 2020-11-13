/*
		���ߣ�Charlie_Xia
		���ܣ��򵥵�����Ԫ����

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
	vector<vector<double>> nodes;			// ����ڵ���������
	nodes = readData_1();					// ��ȡ�ڵ�����
	vector<vector<double>> loads;			// �����غ�����
	loads = readData_2();					// 
	vector<vector<int>> elements;		// ���嵥Ԫ�Ľڵ���
	elements = readData_3();				// 
	vector<vector<double>> bounds;			// ����߽�����
	bounds = readData_4();					// 

	//		���ݽڵ�����������նȾ���
	//		��ʼ������նȾ���

	vector<double> b(2 * nodes.size(), 0);
	vector<vector<double>> K(2 * nodes.size(), b);

	// ���b vector ���һ����ڴ�
	vector<double>().swap(b);

	// ��ʼ����Ԫ�նȾ���
	for (int j = 0; j < 8; j++)
	{
		b.push_back(0);
	}
	vector<vector<double>>Ke(8, b);
	// ���b vector ���һ����ڴ�
	vector<double>().swap(b);

	for (int i = 0; i < elements.size(); i++)				//k����Ԫ��k�ε�Ԫ�նȾ���
	{

		Ke = ElementStiffness(166667, 0.3, 1, nodes[elements[i][0] - 1][0], nodes[elements[i][0] - 1][1],
			nodes[elements[i][1] - 1][0], nodes[elements[i][1] - 1][1], nodes[elements[i][2] - 1][0],
			nodes[elements[i][2] - 1][1], nodes[elements[i][3] - 1][0], nodes[elements[i][3] - 1][1]);

		//���ϵ�����նȾ�����
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




//����߽����������öԽ�Ԫ�ظ�1���Զ�����նȾ���K���غ���������
	for (int i = 0; i < bounds.size(); i++)
	{
		if (bounds[i][0] == 0)
			;//������
		else
		{
			K[2 * i][2 * i] = 1;
			loads[i][0] = 0;
			// һ������0
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
			;//������
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

 // //����
	//for (int i = 0; i < 2 * nodes.size(); i++)
	//{
	//	for (int j = 0; j < 2 * nodes.size(); j++)
	//	{
	//		cout << K[i][j] << "   "  ;
	//	}
	//	cout<<endl;
	//}






	vector<double> F(2 * nodes.size(), 0);

	for (int i = 0; i < nodes.size(); i++)    //�����л�Ϊһ��
	{
		F[2 * i] = loads[i][0];
		F[2 * i + 1] = loads[i][1];
		
	}
	


	//��eigen��ⷽ��
	 MatrixXd Kmatrix(2 * nodes.size(), 2 * nodes.size());
	 VectorXd Fmatrix(2 * nodes.size());

	for (int j = 0; j < 2 * nodes.size(); j++)//��2 * sizeof(nodes)��
	{
		for (int i = 0; i < 2 * nodes.size(); i++)//��2 * sizeof(nodes)�� ���һ��
		{
			Kmatrix(j,i) = K[j][i];
		}
	}

	for (int i = 0; i < 2 * nodes.size(); i++)//��2 * sizeof(nodes)�� ���һ��
	{
		Fmatrix(i) = F[i];
	}

	// QR �ֽ����λ������x
	VectorXd x = Kmatrix.colPivHouseholderQr().solve(Fmatrix);




	//��λ��������Ϊn��2�ľ��󣬷������
	vector<double> s(2, 0);
	vector<vector<double>> X(nodes.size(), s);
	// ���s vector ���һ����ڴ�
	vector<double>().swap(s);
	for (int i = 0; i < 2 * nodes.size(); i = i + 2)    //��һ�л�Ϊ����
	{
		X[i / 2][0] = x(i);
		X[i / 2][1] = x(i + 1);
	}



	//����
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i][0] << "  " << nodes[i][1] << "  " << X[i][0] << "   " << X[i][1] << endl;
	}



	//���Ӧ��
	vector<double> stress_x(nodes.size(), 0);
	vector<double> stress_y(nodes.size(), 0);
	vector<double> stress_xy(nodes.size(), 0);

	double E = 166667, u = 0.3;
	double D[3][3] = { E / (1 - u * u) ,E * u / (1 - u * u) , 0, E * u / (1 - u * u) ,E / (1 - u * u) , 0, 0, 0,(1 - u) * E / (2 * (1 - u * u)) };
	double f[2] = { -0.577350 , 0.577350 };	//������Ҫ������˹���ֵ㣬��ѯ��˹���ֱ�õ�������˹��ĺ���ֵ
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

	






	

	//������
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i][0] << "  " << nodes[i][1] << "  " << X[i][0] << "   " << X[i][1] << "  " << stress_x[i] << "   " << stress_y[i] << "  " << stress_xy[i] << endl;
	}
	
	
	}











