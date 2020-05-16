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

class uslovie
{
public:
	uslovie(string file);
	~uslovie();
	vector <double> cam;
	vector <double> normal;
	vector <double> up;
	double a0;
	double limit;
	double alpha;
	int w;
	int h;
	vector <double> light;
};





