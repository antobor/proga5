#pragma once 
#include "tetra.hpp"
#include "uslovie.hpp"
using namespace std;
vector<tetra*> Readtetra(string file);
double rayIntersectsTriangle(vector <double> p, vector <double> d, vector <double> v0, vector <double> v1, vector <double> v2);
vector<double> rayIntersectsTetra(tetra* T, uslovie A, vector <double> center);
vector<vector<vector<double>>> Getcenters(uslovie A);
void RayTrace(vector<tetra*> arr, uslovie A);