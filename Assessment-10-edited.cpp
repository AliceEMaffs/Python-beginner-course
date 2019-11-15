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
#define EARTH_RADIUS 3958.75 // miles // 6370990.56 in metres

using namespace std;

// define global variables
int f_evals = 0;

// functions 

double fitness(double x, double y) {
	// returns value of functoin to be maximised REMOVE MESSAGE
	double f;
	f = cos(x / 3) * cos(y / 3) * pow(cos(2.*x), 2) * pow(cos(2.*y), 2);
	f_evals++;
	return f;
}

double random_number(double upper, double lower, int n) {
	// returns a random number (type double) between upper and lower REMOVE MESSAGE
	double r;
	r = lower + (rand() % (n + 1) * (1. / n) * (upper - lower));
	return r;
}

// Haversine formula to calculate the Great circle distance
// d for degrees
// function that converts from degrees to radians
double degtorad(double deg) {
	return (deg * (PI / 180));
}

double distance(double latt1d, double longi1d, double latt2d, double longi2d) {

	// set variables for radians
	double latt1r, longi1r, latt2r, longi2r, a, b, Dlongi, Dlatt;

	// converts from degrees to radians
	latt1r = degtorad(latt1d);
	longi1r = degtorad(longi1d);
	latt2r = degtorad(latt2d);
	longi2r = degtorad(longi2d);

	Dlatt = latt2r - latt1r; // difference for latitude
	Dlongi = longi2r - longi1r; // difference for longitude

	a = pow(sin(Dlatt / 2), 2) + cos(latt1r) * cos(latt2r) * pow(sin(Dlongi / 2), 2);
	b = 2 * atan2(sqrt(a), sqrt(1 - a));
	return EARTH_RADIUS * b;

}

// define data structure dataPoint array
struct placedata {
	string place, ttyp;
	double pop, latt, longi;
};

// main program sarts here
int main() {

	// array of point structures to hold the data
	placedata GBplaces[100];
	string data;

	// reading file
	int i = 0;
	double x, y, glx, gly;
	int dx, dy;
	double step = 0.001;
	double value, oldValue, newValue, minValue;
	double globalMin = 0;
	int iteration = 1; // iteration counter

					   // Read in GBplaces
	ifstream inputfile("GBplaces.csv");

	// check if file opened correctly
	if (inputfile.is_open()) {
		// so file is open for reading
		cout << "File successfully opened!\n";
		while (!inputfile.eof()) {

			// while not at the end of the file
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

			if (i > 0) {

				// next ,
				getline(inputfile, data, ',');
				GBplaces[i - 1].place = data;
				//
				getline(inputfile, data, ',');
				GBplaces[i - 1].ttyp = data;
				//
				getline(inputfile, data, ',');
				GBplaces[i - 1].pop = atof(data.c_str());
				//
				getline(inputfile, data, ',');
				GBplaces[i - 1].latt = atof(data.c_str());
				//
				getline(inputfile, data, ',');
				GBplaces[i - 1].longi = atof(data.c_str());

			}

			i++;

		}



		// close the file
		inputfile.close();
	}
	else { // cannot read the file

		cout << "Unable to open the file!\n"; // displays error message
		exit(1);

		cout << GBplaces[i].place << ",";
		cout << GBplaces[i].ttyp << ",";
		cout << GBplaces[i].pop << ",";
		cout << GBplaces[i].latt << ",";
		cout << GBplaces[i].longi << ",";

		cout << "\n";

	}

	// output the first iteration information
	cout << x << " " << y << " -> " << value << "\n";
	// seed random number generator
	srand(time(NULL));
	// start optimization loop
	for (int k = 0; k < 50; k++) {

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
			oldValue = newValue;

			///ADD ANOTHER FOR LOOP HERE, USING i
			
			for (int i = -1; i <= 1; i++) {

				// loop to find next lower value
				for (int j = -1; j >= 1; j++) {

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
							cost += GBplaces[l].pop / minValue;
						}
						// sets the nw value = cost
						newValue = cost;
						// if th new value is smaller than the value
						if (newValue <= value) {

							// ets dx and dy equal to the direction
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
	if (value < globalMin) {

		globalMin = value;

		glx = x;
		gly = y;

	}

	// let user know calculation is progressing
	if (k % 5 == 0) {			
		// message
		cout << "working --" << k << " % complete \n";				
	}

	// output the value for x and y
	cout << "\n";
	cout << "The Best location in the UK for a distribution centre is" << gly << "latitude," << glx << "longitude\n";

	return 0;		///REMOVE THIS FOR NOW
}

///ADD ANOTHER } HERE

//							}
//						}
//			}

/// now work out the value of the function at point x,y
//value = fitness(x, y);

//do {
// now look around the current point and see if we can go somewhere where value is higher
// store values
//oldValue = value;

// see if we can climb
//for (int i = -1; i <= 1; i++) {
//for (int j = -1; j <= 1; j++) {
//if (i == 0 && j == 0) {
//	} else {
// find the value at the test point
//	newValue = fitness(x + step * i, y + step * j);
// bigger than current max value?
//if (newValue <= value) {
//	dx = i;
//	dy = j;
//	value = newValue;
//}
//}
//}
//}
// update to new position and new value
//value = maxValue;
//value = minValue;
//x += step * dx;
//y += step * dy;

// write our the iteration information
//	cout << iteration << " : " << x << "," << y << " : " << value << "\n";

// incremeber iteration counter
//	iteration++;
//	} while (value < oldValue);

//	if (value > globalMin) {
//	globalMin = value;
//glx = x;
//gly = y;
//		}
//	}
//cout << glx << "" << gly << " -> " << globalMin << "\n";
//cout << "Function evaluations" << f_evals << "\n";

//	return 0;
//}


// write our the iteration information
//		cout << iteration << " : " << x << "," << y << " : " << value << "\n";

// incremeber iteration counter
//		iteration++;

//	} while (value < oldValue); // continue loop while still climbing

// finish output number of function evaluations for cost checking


//	if (value > globalMax) {
//		globalMax = value;
//		glx = x;
//		gly = y;
//	}

//}

//cout << glx << " " << gly << " -> " << globalMax << "\n";

//cout << fevals << "\n";

// calculate the sum of the Great Circle distances from point x,y to each place

// greatcircle / population and optimize

// optimize the position x,y

// two hubs??

// trucks back and forth -- improve

// output results

