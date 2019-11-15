// Alice Matthews
// 9464612
// Assessment 10- Optimization
// Program to find best 'Hub' for distribution centre in UK
// Calculates Great-Cirle distace between points using Haversine formula
// weights it with population to find best location for hub


#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#define PI 3.1415926535
#define EARTH_RADIUS 6371.0

using namespace std;

// define global variables
int f_evals = 0;

// functions 

//double fitness(double x, double y) {

//double f;
//f = cos(x / 3) * cos(y / 3) * pow(cos(2.*x), 2) * pow(cos(2.*y), 2);
//f_evals++;
//return f;
//}

// define data structure dataPoint array
struct placedata {
	string place, ttyp;
	double pop, latt, longi;
};
// set random nunmber generator
double random_number(double upper, double lower, int n) {
	double r;
	r = lower + (rand() % (n + 1) * (1. / n) * (upper - lower));
	return r;
}

// Haversine formula to calculate the Great circle distance
// d for degrees
// function that converts from degrees to radians
double degtorad(double deg) {
	return (deg * PI / 180);
}

double distance(double latt1d, double longi1d, double latt2d, double longi2d) {

	// set variables for radians
	double latt1r, longi1r, latt2r, longi2r, Dlongi, Dlatt;

	// converts from degrees to radians
	latt1r = degtorad(latt1d);
	longi1r = degtorad(longi1d);
	latt2r = degtorad(latt2d);
	longi2r = degtorad(longi2d);

	// difference for latitude
	Dlatt = sin((latt2r - latt1r) / 2);
	// difference for longitude
	Dlongi = sin((longi2r - longi1r) / 2);

	//return
	return 2.0 * EARTH_RADIUS * asin(sqrt(Dlatt * Dlatt + cos(latt1r) * cos(latt2r) * Dlongi * Dlongi));

}
// main program sarts here
int main() {

	// array of point structures to hold the data
	placedata GBplaces[100];
	string data;
	string temp;

	// reading file
	double glx, gly;
	int dx, dy;
	double step = 0.01; // TEST CHANGE TO 0.001
	double value, oldValue, newValue, minValue;
	double globalMin = 0;
	int iteration = 1; // iteration counter

	// Read in GBplaces
	ifstream inputfile("GBplaces.csv");

	// check if file opened correctly
	if (inputfile.is_open()) {
		// so file is open for reading
		cout << "File successfully opened!\n\n";
		// set counter to 0
		int i = 0;
		// while not at the end of the file
		for (i = 0; i < 101; i++) {

			if (i == 0) {

				// read first line of data
				getline(inputfile, data, ',');
				// second ,
				getline(inputfile, data, ',');
				// third ,
				getline(inputfile, data, ',');
				// fourth ,
				getline(inputfile, data, ',');
				// fifth and end here
				getline(inputfile, data);
			}
			// if not first line
			if (i > 0) {

				// try next ,
				getline(inputfile, data, ',');
				GBplaces[i-1].place = data;
				//
				getline(inputfile, data, ',');
				GBplaces[i-1].ttyp = data;
				//
				getline(inputfile, data, ',');
				GBplaces[i-1].pop = atof(data.c_str());
				//
				getline(inputfile, data, ',');
				GBplaces[i-1].latt = atof(data.c_str());
				//
				getline(inputfile, data); // GET RID OF LAST COMMA
				GBplaces[i-1].longi = atof(data.c_str());

			}


		}

	}
	// cannot read the file 
	else {

		cout << "Unable to open the file!\n"; // displays error message

		exit(1);

	}
	// close the file
	inputfile.close();
	for (int i = 0; i < 100; i++) {

		//		cout << GBplaces[i].place << ",";
		//		cout << GBplaces[i].ttyp << ",";
		//		cout << GBplaces[i].pop << ",";
		//		cout << GBplaces[i].latt << ",";
		//		cout << GBplaces[i].longi << ",";

		//		cout << "\n";

	}

	// output the first iteration information
	// cout << x << " " << y << " -> " << value << "\n";

	// seed random number generator
	srand(time(NULL));
	// start optimization loop
	for (int k = 0; k < 100; k++) {

		// set the cost value to 0
		double cost = 0;

		// sets the random x and y values
		// used numbers around box of UK to limit distance
		double x = random_number(-6, 3, 100);
		double y = random_number(49, 59, 100);

		// starts the loop for the summing cost
		for (int l = 0; l < 100; l++) {

			// calculates great circle distance
			minValue = abs(distance(y, x, GBplaces[l].latt, GBplaces[l].longi));

			// sums the cost
			cost += minValue / GBplaces[l].pop;
		}

		// sets the cost equal to the value variable
		value = cost;

		// start the loop to find a new higher cost
		do {

			// sets the value equal to the old value for later use
			oldValue = value;

			// loop to find lowest cost for x
			for (int i = -1; i <= 1; i++) {

				// loop to find next lower value for y 
				for (int j = -1; j <= 1; j++) {

					// if centre position, do nothing
					if (i == 0 && j == 0) {

					}

					else {
						// sets the cost = 0
						cost = 0;
						// loop summing cost
						for (int l = 0; l < 100; l++) {

							// calculates great circle distance
							minValue = abs(distance(y + step * j, x + step * i, GBplaces[l].latt, GBplaces[l].longi));

							// sums the cost
							cost += minValue / GBplaces[l].pop;
						}
						// sets the new value = cost
						newValue = cost;

						// if the new value is smaller than the value
						if (newValue <= value) {

							// sets dx and dy equal to the direction
							dx = i;
							dy = j;

							// sets the value equal the newValue
							value = newValue;
						}
					}
				}
			}
			// increases the x and y values by the step and the direction
			x += step * dx;
			y += step * dy;

		} while (value < oldValue);

		// if a larger value was found, replace min with it
		if (value > globalMin) {

			globalMin = value;

			glx = x;
			gly = y;

		}

		// let user know calculation is progressing
		if (k % 10 == 0) {
			// message
			cout << "working --" << k << " % complete \n";
		}
	}

	// output the value for x and y
	cout << "\n";
	cout << "The Best location in the UK for a distribution centre is " << gly << " latitude," << glx << " longitude\n";

	return 0;
}
