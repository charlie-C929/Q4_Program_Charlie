/*
		���ߣ�Charlie_Xia
		�������ã���������

*/




#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include<stdlib.h>
using namespace std;

/*
		����ڵ�����
*/
vector<vector<double>> readData_1()
{
	
	string temp ,temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile,infile1 ;
	infile.open(".\\nodes.txt", ios::in);    // ����ʹ�����·��������ÿ�ζ��޸�
	infile1.open(".\\nodes.txt", ios::in);

	if (!infile && !infile1)
	{
		cout << "fail to open file" << endl;
	}

	infile1 >> temp1;
	while (temp1 != "ENDDATA")
	{
		infile >> temp;
		stringstream ss;
		ss << temp;
		ss >> mindle;
		b.push_back(mindle);

		infile >> temp;
		stringstream ss2;
		ss2 << temp;
		ss2 >> mindle;
		b.push_back(mindle);

		infile1 >> temp1;
		infile1 >> temp1;

		a.push_back(b); 
		b.clear();  // vector ���
	}

	infile.close();
	infile1.close();

	return a;
}


/*
	�����غ�
*/
vector<vector<double>> readData_2()
{

	string temp, temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile, infile1;
	infile.open(".\\loads.txt", ios::in);			// ʹ�����·��
	infile1.open(".\\loads.txt", ios::in);

	if (!infile && !infile1)
	{
		cout << "fail to open file" << endl;

	}

	infile1 >> temp1;
	while (temp1 != "ENDDATA")
	{

		infile >> temp;
		stringstream ss;
		ss << temp;
		ss >> mindle;
		b.push_back(mindle);

		infile >> temp;
		stringstream ss2;
		ss2 << temp;
		ss2 >> mindle;
		b.push_back(mindle);

		infile1 >> temp1;
		infile1 >> temp1;

		a.push_back(b);
		b.clear();  // vector ���
	}

	infile.close();
	infile1.close();

	return a;
}



/*
	
	���뵥Ԫ�ڵ�

*/
vector<vector<double>> readData_3()
{


	string temp, temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile, infile1;
	infile.open(".\\elements.txt", ios::in);
	infile1.open(".\\elements.txt", ios::in);

	if (!infile && !infile1)
	{
		cout << "fail to open file" << endl;

	}

	infile1 >> temp1;
	while (temp1 != "ENDDATA")
	{

		infile >> temp;
		stringstream ss;
		ss << temp;
		ss >> mindle;
		b.push_back(mindle);

		infile >> temp;
		stringstream ss2;
		ss2 << temp;
		ss2 >> mindle;
		b.push_back(mindle);

		infile >> temp;
		stringstream ss3;
		ss3<< temp;
		ss3 >> mindle;
		b.push_back(mindle);

		infile >> temp;
		stringstream ss4;
		ss4 << temp;
		ss4 >> mindle;
		b.push_back(mindle);

		infile1 >> temp1;
		infile1 >> temp1;
		infile1 >> temp1;
		infile1 >> temp1;

		a.push_back(b);
		b.clear();  // vector ���
	}

	infile.close();
	infile1.close();

	return a;


}


/*
	����߽�����
*/
vector<vector<double>> readData_4()
{

	string temp, temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile, infile1;
	infile.open(".\\bounds.txt", ios::in);
	infile1.open(".\\bounds.txt", ios::in);

	if (!infile && !infile1)
	{
		cout << "fail to open file" << endl;

	}

	infile1 >> temp1;
	while (temp1 != "ENDDATA")
	{

		infile >> temp;
		stringstream ss;
		ss << temp;
		ss >> mindle;
		b.push_back(mindle);

		infile >> temp;
		stringstream ss2;
		ss2 << temp;
		ss2 >> mindle;
		b.push_back(mindle);

		infile1 >> temp1;
		infile1 >> temp1;

		a.push_back(b);
		b.clear();  // vector ���
	}

	infile.close();
	infile1.close();

	return a;
}