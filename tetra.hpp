#pragma once 
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <map>
using namespace std;

class tetra
{
public:
	//tetra(vector <double> in, vector<int> c);
	tetra();
	~tetra();
	vector <vector <double>> points;
	void out();
};

