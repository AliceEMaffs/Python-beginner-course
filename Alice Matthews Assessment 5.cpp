// Alice Matthews
// 9464612
// Assessment 5
// Program to reads data points x, y and error s from file
// Computes the erroer-weighted line of best fit through them
// Calculates and displays the chi-squared values for fit obtained

#include <iostream>
#include <fstream>
#include <cmath>

// use standard namespace
using namespace std;

// define data structure called dataPoint
struct dataPoint {
	double x;
	double y;
	double s;
	double w;

};

// main program starts here


int main() {
	// define variables for reading data and calcuating line of best fit and chi squared

	int n = 0;
	double w = 0;		// weight for each point = 1/(s)^2
	double Sw = 0;		// Sw(1) sum of the weights
	double Swx = 0;		// Sw(x) = S(w*x) sum of weights over x values
	double Swy = 0;		// Sw(y) = S(w*y) sum of weights over y values
	double Swxy = 0;	// Sw(x*y) sum of weights of x values multiplied by y values
	double Swxx = 0;	// Sw(x^2) sum of weights of x values squared
	double D;
	double m;			// gradient
	double dm;			// error on gradient
	double c;			// intercept
	double dc;			// error on intercept
	double xsq = 0;		// chi-squared
	double r = 0;		// residual for each point
	
	
	// create an array of dataPoint structures

	dataPoint myPoints[1000];

	// open the file

	ifstream aFile("xys.data.txt");

	// check if file opened correctly

	if (aFile.is_open()) {

		// so file is open for reading

		cout << "File successfully opened!\n";

		while (!aFile.eof()) {
			// while not at the end of the file
			// read from the stream into arrays

			aFile >> myPoints[n].x >> myPoints[n].y >> myPoints[n].s;
			n++; // increment array index counter n = n + 1
		}
		// close the file
		aFile.close();
	}

	// cannot read the file

	else {
		cout << "Unable to open the file!\n"; // displays error message
		exit(1);
	}

	cout << " n = " << n << endl;
	// output data points to check if they were read correctly

	for (int i = 0; i < n; i++) {
		//if (myPoints[i].x > -100000) {
			printf("x = %8.4f, y = %8.4f, s = %8.4f\n", myPoints[i].x, myPoints[i].y, myPoints[i].s); // prints the array
	//	}
	}

	// compute line of best fit

		for (int i = 0; i < n; i++) {

			w = 1 / pow(myPoints[i].s,2);
			Sw = Sw + w;
			Swx = Swx + w * myPoints[i].x;
			Swy = Swy + w * myPoints[i].y;
			Swxy = Swxy + w * myPoints[i].x * myPoints[i].y;
			Swxx = Swxx + w * myPoints[i].x * myPoints[i].x;
	}

	// for line of best fit parameters
	
	D = (Sw * Swxx - pow(Swx,2));
	m = (Sw * Swxy - Swx * Swy) / D;
	dm = sqrt(Sw / D);
	c = (Swy * Swxx - Swx * Swxy) / D;
	dc = sqrt(Swxx) / D;
	
	// compute chi-sqaured

	for (int k = 0; k < n; k++) {
		double a = (m * myPoints[k].x + c - myPoints[k].y) / myPoints[k].s;
		xsq = xsq + pow(a, 2);
	}

	// output results to the screen

	printf("\nThe error-weighted line of best fit is given by \n\ny =");
	printf("%8.4fx +%8.4f\n\nwith errors on gradient dm = %8.4f, and on intercept dc = %8.4f \n", m, c, dm, dc);
	printf("\nThe value for chi squared = %8.4f\n\n",  xsq);
	
	return 0;
}