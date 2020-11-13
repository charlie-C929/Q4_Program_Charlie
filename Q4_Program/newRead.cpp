#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<stdio.h>
#include "newRead.hpp"

using namespace std;


//第一个函数取节点坐标
struct dataX_r node()
{
    dataX_r c;
    //首先把所有字符都输入到字符串A中
    vector<string> A;
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



    //获取节点坐标
    //先把节点坐标的字符串导入
    vector<string> tempnodes;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] == "*NODE")
        {
            for (int j = i + 1; j < A.size() - i; j++)
            {
                if (A[j] == "*ELEMENT_SHELL")
                    break;
                tempnodes.push_back(A[j]);

            }
        }
    }

    //初始化nodes
    vector<double> b(2, 0);
    for (int i = 0; i < tempnodes.size(); i++)
    {
        c.nodes.push_back(b);
    }

    //把节点坐标的字符串变成数字
    for (int i = 0; i < tempnodes.size(); i++)
    {
        string temp = tempnodes[i];
        string x = temp.substr(9, 15);
        string y = temp.substr(25, 15);
        c.nodes[i][0] = stod(x);
        c.nodes[i][1] = stod(y);
        cout << c.nodes[i][0] << endl;
    }


    ////取单元节点
    //vector<string> tempelements;
    //for (int i = 0; i < A.size(); i++)
    //{
    //    if (A[i] == "*ELEMENT_SHELL")
    //    {
    //        for (int j = i + 1; j < A.size() - i; j++)
    //        {
    //            if (A[j] == "*LOAD_NODE_POINT")
    //                break;
    //            tempelements.push_back(A[j]);

    //        }
    //    }
    //}


    return c;
}















