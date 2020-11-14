#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;
// ÉùÃ÷
extern struct dataX_r {
    vector<vector<double>> nodes;
    vector<vector<double>> elements;
    vector<vector<double>>loads;
    vector<vector<double>>bounds;
};
// ÉùÃ÷
struct dataX_r node();