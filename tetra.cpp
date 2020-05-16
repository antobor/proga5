#include "tetra.hpp"
using namespace std;


/*tetra::tetra(vector<double> in, vector<int> c){
	points = in;
	color = c;
}*/


tetra::~tetra()
{
}


tetra::tetra() {
	vector <double> in(3, 0);
	vector <vector <double>> in1(4);
	points = in1;
#pragma omp parallel for
	for (int i = 0;unsigned int(i) < points.size();i++) {
		points[i] = in;
	}
}

void tetra::out() {
	cout << "points"<<endl;
	for (size_t i = 0;i < points.size();i++) {
//#pragma omp parallel for
		for (int j = 0;unsigned int(j) < points[i].size();j++) {
			cout << points[i][j] << " ";
		}
	}
	cout << endl;
}