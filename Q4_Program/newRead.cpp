#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<stdio.h>
#include "newRead.hpp"

using namespace std;


//��һ������ȡ�ڵ�����
struct dataX_r node()
{
    dataX_r c;
    //���Ȱ������ַ������뵽�ַ���A��
    vector<string> A;
    string a;
    ifstream infile;
    infile.open(".\\mesh.k", ios::in);
    if (!infile)
    {
        cout << "fail to open file" << endl;
    }
    int i = 0;
    while (getline(infile, a))     //k�ļ��е������ַ����������ַ������Ѿ�������A
    {
        A.push_back(a);
    }



    //��ȡ�ڵ�����
    //�Ȱѽڵ�������ַ�������
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

    //��ʼ��nodes
    vector<double> b(2, 0);
    for (int i = 0; i < tempnodes.size(); i++)
    {
        c.nodes.push_back(b);
    }

    //�ѽڵ�������ַ����������
    for (int i = 0; i < tempnodes.size(); i++)
    {
        string temp = tempnodes[i];
        string x = temp.substr(9, 15);
        string y = temp.substr(25, 15);
        c.nodes[i][0] = stod(x);
        c.nodes[i][1] = stod(y);
        cout << c.nodes[i][0] << endl;
    }


    ////ȡ��Ԫ�ڵ�
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















