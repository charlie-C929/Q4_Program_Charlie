#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<stdio.h>

using namespace std;


struct data {
    //��һ������ȡ�ڵ�����
    vector<string> nodes()
    {

        //���Ȱ������ַ������뵽�ַ���A��
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
        while (getline(infile, a))     //k�ļ��е������ַ����������ַ������Ѿ�������A
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
















