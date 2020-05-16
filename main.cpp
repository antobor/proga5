#pragma once
#include "func.hpp"
#include "tetra.hpp"
#include "uslovie.hpp"
#include "CImg.h"
using namespace std;

int main()
{
	uslovie A("input_all.txt");
	vector<tetra*> arr;
	arr = Readtetra("input_tetra.txt");
	for (size_t i = 0;i < arr.size();i++) {
		arr[i]->out();
	}
	RayTrace(arr, A);
	cout << "hotovo" << endl;
	for (size_t j = 0;j < arr.size();j++) {
		delete arr[j];
	}
	string aaa;
	cin >> aaa;

    return 0;
}

//using namespace cimg_library;

/*int main() {
	CImg<unsigned char> img(640, 400, 1, 3);
	img.fill(0);
	unsigned char purple[] = { 255,0,255 };
	img.draw_text(100, 100, "Hello World", purple);
	img.display("My first CImg code");
	return 0;
}*/