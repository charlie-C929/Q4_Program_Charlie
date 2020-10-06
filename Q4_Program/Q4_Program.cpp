
/*
        程序作者：Max_Zhang
        程序功能：等参单元四节点，Q4_Program 主程序
*/

#include <iostream>
#include <vector>
#include "ex1.hpp"
#include "shapeFuncAndDiff.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    ex1();
    double s = 0.5, t = 0.5;
    double *N = shapeFunc(s, t);
    cout << N[0] << N[1] << N[2] << N[3] << endl;
}
