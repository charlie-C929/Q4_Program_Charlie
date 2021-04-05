#ifndef IO_CPP
#define IO_CPP
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;
vector<string> readFile(string filename);
void writeFile(string filename,const vector<string> &A);
#endif