/*
		作者：Charlie_Xia
		程序作用：读入数据

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
		读入节点坐标
*/
vector<vector<double>> readData_1()
{
	
	string temp ,temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile,infile1 ;
	infile.open(".\\nodes.txt", ios::in);    // 这里使用相对路径，以免每次都修改
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
		b.clear();  // vector 清空
	}

	infile.close();
	infile1.close();

	return a;
}


/*
	读入载荷
*/
vector<vector<double>> readData_2()
{

	string temp, temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile, infile1;
	infile.open(".\\loads.txt", ios::in);			// 使用相对路径
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
		b.clear();  // vector 清空
	}

	infile.close();
	infile1.close();

	return a;
}



/*
	
	读入单元节点

*/
vector<vector<int>> readData_3()
{


	string temp, temp1;
	int mindle = 0;
	vector<vector<int>> a;
	vector<int> b;
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
		b.clear();  // vector 清空
	}

	infile.close();
	infile1.close();

	return a;


}


/*
	读入边界条件
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
		b.clear();  // vector 清空
	}

	infile.close();
	infile1.close();

	return a;
}