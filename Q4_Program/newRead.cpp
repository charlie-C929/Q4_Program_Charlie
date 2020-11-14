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
            for (int j = i + 1; j < A.size(); j++)
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
    for (int i =0; i < tempnodes.size(); i++)
    {
       string temp = tempnodes[i];
        string x = temp.substr(9, 15);
        string y=temp.substr(25, 15);
        c.nodes[i][0] = stod(x);
        c.nodes[i][1] = stod(y);
    }

    //获取每个单元的节点序号
    //取每个单元的节点序号
    vector<string> tempelements;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] == "*ELEMENT_SHELL")
        {
            for (int j = i + 1; j < A.size(); j++)
            {
                if (A[j] == "*LOAD_NODE_POINT")
                    break;
                tempelements.push_back(A[j]);

            }
        }
    }
   

    //初始化elements
    vector<double> b1(4, 0);
    for (int i = 0; i < tempelements.size(); i++)
    {
        c.elements.push_back(b1);
    }

    //把单元节点序号的字符串变成数字
    for (int i = 0; i < tempelements.size(); i++)
    {
        string temp = tempelements[i];
        string n1 = temp.substr(21, 3);
        string n2 = temp.substr(29, 3);
        string n3 = temp.substr(37, 3);
        string n4 = temp.substr(45, 3);
        c.elements[i][0] = stod(n1);
        c.elements[i][1] = stod(n2);
        c.elements[i][2] = stod(n3);
        c.elements[i][3] = stod(n4);
        /*cout << c.elements[i][0] << "  " << c.elements[i][1] << "  " << c.elements[i][2] << "  " << c.elements[i][3] << endl;*/
    }

   
    //获取施加的外力

    vector<string> temploads;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] == "*LOAD_NODE_POINT")
        {
            for (int j = i + 1; j < A.size(); j++)
            {
                if (A[j] == "*BOUNDARY_SPC_NODE")
                    break;
                temploads.push_back(A[j]);

            }
        }
    }

    //初始化loads
    vector<double> b2(2, 0);
    for (int i = 0; i < c.nodes.size(); i++)
    {
        c.loads.push_back(b2);
    }

    //把loads字符串变成数字
    for (int i = 2; i < temploads.size(); i++)
    {
        string temp = temploads[i];
        string n = temp.substr(7, 3);
        string x = temp.substr(36, 4);
        string y = temp.substr(49, 1);
        int num = stoi(n);
        c.loads[num-1][0] = stod(x);
        c.loads[num-1][1] = stod(y);
       
    }

    /*for (int i = 0; i < c.loads.size(); i++)
    {
        cout << c.loads[i][0] << "  " << c.loads[i][1] << endl;
    }*/
    


    //获取边界条件

    vector<string> tempbounds;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] == "*BOUNDARY_SPC_NODE")
        {
            for (int j = i + 1; j < A.size(); j++)
            {
                if (A[j] == "*END")
                    break;
                tempbounds.push_back(A[j]);

            }
        }
    }


    //初始化bounds
    vector<double> b3(2, 0);
    for (int i = 0; i < c.nodes.size(); i++)
    {
        c.bounds.push_back(b3);
    }

 
    //把bounds字符串变成数字
    for (int i = 2; i < tempbounds.size(); i++)
    {
        string temp = tempbounds[i];
        string n = temp.substr(7, 3);
        string x = temp.substr(29, 1);
        string y = temp.substr(39, 1);
        int num = stoi(n);
        if (x!=" ")
        c.bounds[num - 1][0] = stod(x);
        if (y!=" ")
        c.bounds[num - 1][1] = stod(y);

    }

   

    return c;
}















