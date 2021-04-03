#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class node
{
private:
    vector<string> readFile(const string &filename);
    vector<string> initNodes(const vector<string> &A);

public:
    vector<vector<double>> nodes;
    vector<vector<double>> elements;
    vector<vector<double>> loads;
    vector<vector<double>> bounds;
    node(const string &filename);
    node(const vector<string> &filename);
};