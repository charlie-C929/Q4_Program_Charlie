#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include "IO.hpp"
using namespace std;

vector<string> readFile(string filename)
{
	vector<string> A;
	string temp;
	ifstream input;
	input.open(filename, ios::in);
	if (!input.is_open())
	{
		cout << "can not open input" << endl;
		return A;
	}
	while (getline(input, temp))
	{
		A.push_back(temp);
	}
	input.close();
	return A;
}

void writeFile(string filename, const vector<string> &A)
{
	ofstream outFile;
	outFile.open(filename);
	if (!outFile.is_open())
	{
		cout << "can not open output file,chack your authority!" << endl;
	}
	else
	{
		outFile << "TITLE = 'RESULT'" << endl;
		outFile << "VARIABLES = 'X','Y','Z','xstrain', 'ystrain', 'xStress', 'yStress', 'xyStress'" << endl;
		for (auto i : A)
		{
			outFile << i << endl;
		}
	}
}
