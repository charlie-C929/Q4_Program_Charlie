
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include<stdlib.h>
using namespace std;


vector<vector<double>> readData_1()
{
	

	/*
		����ڵ�����
	*/
	string temp ,temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile,infile1 ;
	infile.open("C:\\Users\\liuyina\\Desktop\\Q4_xia\\nodes.txt", ios::in);
	infile1.open("C:\\Users\\liuyina\\Desktop\\Q4_xia\\nodes.txt", ios::in);

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



vector<vector<double>> readData_2()
{


	/*
		����Ӧ��
	*/
	string temp, temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile, infile1;
	infile.open("C:\\Users\\liuyina\\Desktop\\Q4_xia\\loads.txt", ios::in);
	infile1.open("C:\\Users\\liuyina\\Desktop\\Q4_xia\\loads.txt", ios::in);

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



/*���뵥Ԫ�ڵ�


*/
vector<vector<double>> readData_3()
{


	string temp, temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile, infile1;
	infile.open("C:\\Users\\liuyina\\Desktop\\Q4_xia\\elements.txt", ios::in);
	infile1.open("C:\\Users\\liuyina\\Desktop\\Q4_xia\\elements.txt", ios::in);

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



vector<vector<double>> readData_4()
{


	/*
		����߽�����
	*/
	string temp, temp1;
	double mindle = 0;
	vector<vector<double>> a;
	vector<double> b;
	ifstream infile, infile1;
	infile.open("C:\\Users\\liuyina\\Desktop\\Q4_xia\\bounds.txt", ios::in);
	infile1.open("C:\\Users\\liuyina\\Desktop\\Q4_xia\\bounds.txt", ios::in);

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