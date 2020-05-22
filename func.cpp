#pragma once 
#include "func.hpp"
#include <algorithm>
#include <cmath>
#include "CImg.h"
#include <chrono>
#define pi 3.14159265 
using namespace std;

vector<tetra*> Readtetra(string file) {
	ifstream in(file);
	if (!in) {
		cout << "file error" << endl;
		exit(0);
	}
	vector<tetra*> arr;
	string name;
	
	tetra* newV;
	while (!in.eof()) {
		cout << "adadajdlka" << endl;
		newV = new tetra;
		in >> name;

		for (size_t i = 0;i < newV->points.size();i++) {
			for (int j = 0;unsigned int(j) < newV->points[i].size();j++) {
				in >> newV->points[i][j];
			}
		}
		arr.push_back(newV);
	}
	return arr;
}
#define vector(a,b,c) \
	(a)[0] = (b)[0] - (c)[0];	\
	(a)[1] = (b)[1] - (c)[1];	\
	(a)[2] = (b)[2] - (c)[2];

#define crossProduct(a,b,c) \
(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];

#define innerProduct(v,q) \
((v)[0] * (q)[0] + \
(v)[1] * (q)[1] + \
(v)[2] * (q)[2])

double rayIntersectsTriangle(vector <double> p, vector <double> d,vector <double> v0, vector <double> v1, vector <double> v2) {

	vector <double> e1(3), e2(3), h(3), s(3), q(3);
	double a, f, u, v, t;
	vector(e1, v1, v0);
	vector(e2, v2, v0);

	crossProduct(h, d, e2);
	a = innerProduct(e1, h);

	if (a > -0.00001 && a < 0.00001) { 
		return -1; 
	}

	f = 1 / a;
	vector(s, p, v0);
	u = f * (innerProduct(s, h));

	if (u < 0.0 || u > 1.0) {
		return -1;
	}
	crossProduct(q, s, e1);
	v = f * innerProduct(d, q);

	if (v < 0.0 || u + v > 1.0) {
		return -1;
	}
	t = f * innerProduct(e2, q);

	if (t > 0.00001) {
		return t;
	}
	else {
		return -1;
	}
}


vector<double> rayIntersectsTetra(tetra* T, uslovie A, vector <double> center) {
	vector<double> d(3), t(4),vec(3), bin(3), normn(3),lim(3),ptetra(3),e1(3),e2(3),nn(3),tp(3),temp(3), normnn(3),lv(3),normlv(3),nool(2,0);
	double tmin, tscreen,c1,c2,c3,coef;
	vector(d, center, A.cam);
#pragma omp parallel for
	for (int i = 0;i < 4;i++) {
		t[i]=rayIntersectsTriangle(A.cam, d, T->points[i], T->points[(i + 1) % 4], T->points[(i + 2) % 4]);
	}
	int k = 0;
	vector<int> kk;
	tscreen = (center[0] - A.cam[0]) / d[0];
	for (int i= 0;unsigned int(i) < t.size();i++) {
		if (t[i] <= tscreen) {
			t.erase(t.begin() + i);
			i--;
		}
		else {
			kk.push_back(k);
		}
		k++;
	}
	if (t.size() == 0) {
		return nool;
	}
	vector<double>::iterator result = min_element(t.begin(), t.end());
	tmin = *result;
	int itmin=0;
	while (result != t.begin()) {
		result--;
		itmin++;
	}
	for (int i = 0;i < 3;i++) {
		normn[i] = A.normal[i] / sqrt(pow(A.normal[0], 2) + pow(A.normal[1], 2) + pow(A.normal[2], 2));
	}
	for (int i = 0;i < 3;i++) {
		lim[i] = A.cam[i] + A.limit * normn[i];
	}
	c1 = A.normal[0] * (A.cam[0] - lim[0]) + A.normal[1] * (A.cam[1] - lim[1]) + A.normal[2] * (A.cam[2] - lim[2]);
	for (int i = 0;i < 3;i++) {
		ptetra[i] = A.cam[i] + tmin * d[i];
	}
	c2 = A.normal[0] * (ptetra[0] - lim[0]) + A.normal[1] * (ptetra[1] - lim[1]) + A.normal[2] * (ptetra[2] - lim[2]);
	c3 = c1 * c2;
	if (c3 <= 0) {
		return nool;
	}
	vector(e1, T->points[kk[itmin]], T->points[(kk[itmin ] + 1) % 4]);
	vector(e2, T->points[kk[itmin]], T->points[(kk[itmin ] + 2) % 4]);
	crossProduct(nn, e1, e2);
	for (int i = 0;i < 3;i++) {
		tp[i] = ptetra[i] + nn[i];
	}
	vector(temp, tp, ptetra);
	c1 = innerProduct(nn,temp);
	vector(temp, T->points[(kk[itmin] + 3) % 4], ptetra);
	c2 = innerProduct(nn, temp);
	c3 = c1 * c2;
	if (c3 >= 0) {
		for (int i = 0;i < 3;i++) {
			nn[i] = -1*nn[i];
		}
	}
	for (int i = 0;i < 3;i++) {
		normnn[i] = nn[i] / sqrt(pow(nn[0], 2) + pow(nn[1], 2) + pow(nn[2], 2));
	}
	vector(lv, A.light, ptetra);
	for (int i = 0;i < 3;i++) {
		normlv[i] = lv[i] / sqrt(pow(lv[0], 2) + pow(lv[1], 2) + pow(lv[2], 2));
	}
	coef = innerProduct(normnn, normlv);
	if (coef <= 0) {
		coef = 0;
	}
	vector<double> res;
	res.push_back(tmin);
	res.push_back(coef);
	return res;
}


vector<vector<vector<double>>> Getcenters(uslovie A) {
	vector<vector<vector<double>>> centers(A.w);
	vector<vector<double>> nool2(A.h);
	vector<double> normn(3),nup(3),bin(3),ugl(3),nool(3,0);
	double H, x;
	H = 2 * A.a0 * tan((A.alpha * pi) / 360);
	x = H / A.h; // ðåàëüíûé ðàçìåð ïèêñåëÿ
	for (int i = 0;i < 3;i++) {
		normn[i] = A.normal[i] / sqrt(pow(A.normal[0],2) + pow(A.normal[1], 2) + pow(A.normal[2], 2));
	}
	for (int i = 0;i < 3;i++) {
		nup[i] = A.up[i] / sqrt(pow(A.up[0], 2) + pow(A.up[1], 2) + pow(A.up[2], 2));
	}
	crossProduct(bin, nup, normn);
	for (int i = 0;i < 3;i++) {
		ugl[i] = A.cam[i] + A.a0 * normn[i] + (H/2) * nup[i] + (A.w*x*bin[i])/2;
	}
	for (int i = 0;unsigned int(i) < centers.size();i++) {
		centers[i] = nool2;
	}

	for (size_t i = 0;i < centers.size();i++) {
		for (int j = 0;unsigned int(j) < centers[i].size();j++) {
			centers[i][j]=nool;
		}
	}
	for (int i = 0;unsigned int(i) < centers.size();i++) {
#pragma omp parallel for
		for (int j = 0;unsigned int(j) < centers[i].size();j++) {
#pragma omp parallel for
			for (int k = 0;unsigned int(k) < centers[i][j].size();k++) {
				centers[i][j][k] = ugl[k] - (0.5 +j)*x*nup[k] - (0.5 + i)*x*bin[k];
			}
		}
	}
	
	return centers;

}


void RayTrace(vector<tetra*> arr, uslovie A) {
	vector<vector<vector<double>>> centers;
	double smallo;
	cimg_library::CImg<unsigned char> img(A.w, A.h, 1, 3);
	img.fill(255);
	unsigned char blue[] = { 0,0,255 };
	chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
	centers = Getcenters(A);
#pragma omp parallel for
	for (int i = 0;unsigned int(i) < centers.size();i++) {
#pragma omp parallel for
		for (int j = 0;unsigned int(j) < centers[i].size();j++) {
			vector<vector<double>> fulldata;
			vector<double> data;
			for (size_t k = 0;k < arr.size();k++) {
				data = rayIntersectsTetra(arr[k], A, centers[i][j]);
				fulldata.push_back(data);
			}
			for (size_t i = 0;i < fulldata.size();i++) {
				if (fulldata[i][0] ==0) {
					fulldata.erase(fulldata.begin() + i);
					i--;
				}
			}

			if (fulldata.size() == 0) {
				continue;
			}

			smallo = fulldata[0][0];
			int smalli = 0;

			for (size_t i = 0;i < fulldata.size();i++) {
				if (fulldata[i][0] <= smallo) {
					smallo = fulldata[i][0];
					smalli = i;
				}
			}
			double color = 255 * fulldata[smalli][1];
			unsigned char temp[] = { 0, 0 ,unsigned char(color) };
			img.draw_point(i, j, temp);
			fulldata.clear();
		}
	}
	chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
	int elapsed_ms = static_cast<int>(chrono::duration_cast<chrono::milliseconds>(end - start).count());
	std::cout << "Prog runtime is " << elapsed_ms << " ms\n";
	img.save("res.bmp");
	img.display("RayTracing");
}



