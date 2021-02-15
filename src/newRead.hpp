#ifndef NEWREAD_HPP
#define NEWREAD_HPP
#include<iostream>
#include<vector>
#include<string>
using namespace std;
// 声明
struct dataX_r {
    vector<vector<double>> nodes;
    vector<vector<double>> elements;
    vector<vector<double>>loads;
    vector<vector<double>>bounds;
};
// 声明
struct dataX_r node();
#endif