#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<stdio.h>

using namespace std;


struct data {
    //第一个函数取节点坐标
    vector<string> nodes()
    {

        //首先把所有字符都输入到字符串A中
        vector<string> A;
        vector<string>nodes;
        string a;
        ifstream infile;
        infile.open(".\\mesh.k", ios::in);
        if (!infile)
        {
            cout << "fail to open file" << endl;
        }
        int i = 0;
        while (getline(infile, a))     //k文件中的所有字符（包括空字符）都已经付给了A
        {
            A.push_back(a);
        }
        for (int i = 0; i < A.size(); i++)
        {
            if (A[i] == "*NODE")
            {
                for (int j = i + 1; j < A.size() - i; j++)
                {
                    if (A[j] == "*ELEMENT_SHELL")
                        break;
                    nodes.push_back(A[j]);
                    
                }
            }

        }
        return nodes;
    }




};
















