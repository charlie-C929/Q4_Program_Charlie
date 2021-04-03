#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class node
{
private:
    //读取文件
    vector<string> readFile(const string &filename)
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
    //初始化node
    void initNodes(const vector<string> &A)
    {
        auto i = A.cbegin();
        vector<string> tempNodes;
        while (i != A.cend())
        {
            if (*i == "*NODE")
            {
                for (auto j = i + 1; j != A.cend(); j++)
                {
                    if (*j == "*ELEMENT_SHELL")
                    {
                        break;
                    }
                    tempNodes.push_back(*j);
                }
            }
            ++i;
        }
        //初始化nodes
        vector<double> b(2, 0);
        for (auto _ : tempNodes)
        {
            this->nodes.push_back(b);
        }
        //将字符串转换成数字
        for (size_t i = 0; i < tempNodes.size(); ++i)
        {
            string temp = tempNodes[i];
            string x = temp.substr(9, 15);
            string y = temp.substr(25, 15);
            this->nodes[i][0] = stod(x);
            this->nodes[i][1] = stod(y);
        }
        //获取每个单元的节点序号
        vector<string> tempelements;
        for (auto i = A.cbegin(); i != A.cend(); ++i)
        {
            if (*i == "*ELEMENT_SHELL")
            {
                for (auto j = i + 1; j != A.cend(); ++j)
                {
                    if (*j == "*LOAD_NODE_POINT")
                        break;
                    tempelements.push_back(*j);
                }
            }
        }
        //初始化elements
        vector<double> b1(4, 0);
        for (auto _ : tempelements)
        {
            this->elements.push_back(b1);
        }
        for (size_t i = 0; i < tempelements.size(); i++)
        {
            string temp = tempelements[i];
            string n1 = temp.substr(17, 7);
            string n2 = temp.substr(25, 7);
            string n3 = temp.substr(33, 7);
            string n4 = temp.substr(41, 7);
            this->elements[i][0] = stod(n1);
            this->elements[i][1] = stod(n2);
            this->elements[i][2] = stod(n3);
            this->elements[i][3] = stod(n4);
        }
        //获取施加的外力
        vector<string> temploads;
        for (auto i = A.begin(); i != A.end(); ++i)
        {
            if (*i == "*LOAD_NODE_POINT")
            {
                for (auto j = i + 3; j != A.cend(); ++j)
                {
                    if (*j == "*BOUNDARY_SPC_NODE")

                        break;
                    temploads.push_back(*j);
                }
            }
        }

        //初始化loads
        vector<double> b2(2, 0);
        for (auto _ : this->nodes)
        {
            this->loads.push_back(b2);
        }
        for (size_t i = 0; i < temploads.size(); i++)
        {
            string temp = temploads[i];
            string n = temp.substr(5, 5);
            string x = temp.substr(32, 9);
            string y = temp.substr(42, 9);
            int num = stoi(n);
            this->loads[num - 1][0] = stod(x);
            this->loads[num - 1][1] = stod(y);
        }

        //初始化
        //获取边界条件

        vector<string> tempbounds;
        for (auto i = A.cbegin(); i != A.cend(); ++i)
        {
            if (*i == "*BOUNDARY_SPC_NODE")
            {
                for (auto j = i + 3; j != A.cend(); ++j)
                {
                    if (*j == "*END")
                        break;
                    tempbounds.push_back(*j);
                }
            }
        }

        //初始化bounds
        for (auto _ : this->nodes)
        {
            this->bounds.push_back(vector<double>(2, 0));
        }

        //把bounds字符串变成数字
        for (size_t i = 0; i < tempbounds.size(); i++)
        {
            string temp = tempbounds[i];
            string n = temp.substr(5, 5);
            string x = temp.substr(29, 1);
            string y = temp.substr(39, 1);
            int num = stoi(n);
            if (x != " ")
                this->bounds[num - 1][0] = stod(x);
            if (y != " ")
                this->bounds[num - 1][1] = stod(y);
        }
    }

public:
    vector<vector<double>> nodes;
    vector<vector<double>> elements;
    vector<vector<double>> loads;
    vector<vector<double>> bounds;
    //构造函数,通过读取文件
    node(const string &filename);
    //构造函数,通过传入原始字符串vector
    node(const vector<string> &filename);
};

node::node(const string &filename)
{
    initNodes(readFile(filename));
}
node::node(const vector<string> &A)
{
    initNodes(A);
}
