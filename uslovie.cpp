#include "uslovie.hpp"





uslovie::uslovie(string file) {
	ifstream in(file);
	if (!in) {
		cout << "file error" << endl;
		exit(0);
	}
	string type;
	double temp1, temp2, temp3;
	in >> type; //cam
	cam.reserve(3);
	in >> temp1 >> temp2 >> temp3;
	cam.push_back(temp1);
	cam.push_back(temp2);
	cam.push_back(temp3);
	in >> type; //normal
	in >> temp1 >> temp2 >> temp3;
	normal.push_back(temp1);
	normal.push_back(temp2);
	normal.push_back(temp3);
	in >> type; //up
	in >> temp1 >> temp2 >> temp3;
	up.push_back(temp1);
	up.push_back(temp2);
	up.push_back(temp3);
	in >> type; //screen
	in >> a0;
	in >> type; //limit
	in >> limit;
	in >> type; //alpha
	in >> alpha;
	in >> type; //width
	in >> w;
	in >> type; //height
	in >> h;
	in >> type; //light
	in >> temp1 >> temp2 >> temp3;
	light.push_back(temp1);
	light.push_back(temp2);
	light.push_back(temp3);
}
uslovie::~uslovie() {
}