#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#define TOLERANCE 1e-14
using namespace std;

int main() {
	vector < vector<double> > a;
	string aLine;
	int cumulativeRowSize = 0;
	int rowSize;



	int matrixType;
	cout << "Would you like to: \n1)find the inverse of a matrix or \n2)solve a set of linear equations?\n";
	cin >> matrixType;

	/**************open file and read in lines to matrix a**************/
	ifstream theFile("random_matrix.csv");
	if (theFile.is_open()) {
		while (!theFile.eof()) {
			int start = 0;
			int end = 0;
			double temp;
			vector <double> tempVector;
			getline(theFile, aLine);
			if (aLine.length() != 0) {
				while (end < aLine.length()) {
					end = aLine.find(",", start);
					//accomodates for final value that does not finish with comma
					if (end == string::npos) {
						end = aLine.length();
						// adds substring starting after comma finishing end of line to variable
						temp = atof(aLine.substr(start, end).c_str());
					}
					//finds values between commas
					else {
						temp = atof(aLine.substr(start, end).c_str());
					}
					tempVector.push_back(temp);
					start = end + 1;
					cumulativeRowSize++;
				}
				int n = tempVector.size();
				//allow identity matrix to be added to form augmented matrix
				if (matrixType == 1) {
					for (int i = 0; i < n; i++) {
						tempVector.push_back(0);
					}
				}
				//puts rows into column vector;
				a.push_back(tempVector);
			}
		}
		theFile.close();
		//calculate size of each row
		rowSize = cumulativeRowSize / a.size();
	}
	else {
		cout << "Unable to open the file for reading\n";
		// stop the program
		exit(1);
	}
	/***********************Inverting matrix method***********************/
	if (matrixType == 1) {
		int n = rowSize;
		//ensure program runs only if matrix of the form (n x n)
		if (n == a.size()) {

			cout << "Matrix:\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					cout << a[i][j] << ",        ";
				}
				cout << "\n";
			}

			//add on augmented matrix
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < 2 * n; j++) {
					if (j == (i + n)) {
						a[i][j] = 1;
					}
				}
			}

			//print out augmented matrix
			cout << "\nAugmented Matrix:\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j == n - 2) {
						cout << a[i][j] << ":        ";
					}
					else if (j == n - 1) {
						cout << a[i][j] << " ";
					}
					else {
						cout << a[i][j] << ",        ";
					}
				}
				cout << "\n";
			}

			//pivot matrix
			for (int i = 0; i < n - 1; i++) {
				for (int k = 1; k < n - i; k++) {
					if (abs(a[i][0]) < abs(a[i + k][0])) {
						for (int j = 0; j < n * 2; j++) {
							double x = a[i + k][j];
							a[i + k][j] = a[i][j];
							a[i][j] = x;
						}
					}
				}
			}
			//ensure diagonal is non zero
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n * 2; j++) {
					if (a[i][i] == 0) {
						if (i != 0) {
							a[i][j] = a[i][j] + a[i - 1][j];
						}
						else {
							a[i][j] = a[i][j] + a[i + 1][j];
						}
					}
				}
			}

			//print out pivoted matrix
			cout << "\npivoted output:\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n * 2; j++) {
					if (j == n - 2) {
						cout << a[i][j] << ":        ";
					}
					else if (j == n - 1) {
						cout << a[i][j] << " ";
					}
					else {
						cout << a[i][j] << ",        ";
					}
				}
				cout << "\n";
			}


			//reduce to echelon matrix
			for (int i = 0; i < n; i++) {
				for (int k = 1; k < n; k++) {
					if (k > i) {
						double b = a[k][i] / a[i][i];
						for (int j = 0; j < 2 * n; j++) {
							a[k][j] = a[k][j] - b*a[i][j];
						}
					}
				}
			}
			//reduce to echelon by making diagonals 1
			for (int i = 0; i < n; i++) {
				double x = a[i][i];
				for (int j = 0; j < n * 2; j++) {
					a[i][j] = a[i][j] / x;
				}
			}

			//print out echelon matrix
			cout << "\nechelon matrix:\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < 2 * n; j++) {
					if (j == n - 2) {
						cout << a[i][j] << ":        ";
					}
					else if (j == n - 1) {
						cout << a[i][j] << " ";
					}
					else {
						cout << a[i][j] << ",        ";
					}
				}
				cout << "\n";
			}


			//do back substitution 
			for (int i = n - 1; i >= 0; i--) {
				for (int k = n - 1; k >= 0; k--) {
					if (k < i) {
						double b = a[k][i] / a[i][i];
						for (int j = 0; j < 2 * n; j++) {
							a[k][j] = a[k][j] - b*a[i][j];
						}
					}
				}
			}

			//round answer to zero for very small values
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n * 2; j++) {
					if (abs(a[i][j]) < TOLERANCE) {
						a[i][j] = 0;
					}
				}
			}

			//print out diagonalized matrix
			cout << "\ndiagonalized matrix:\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < 2 * n; j++) {
					if (j == n - 2) {
						cout << a[i][j] << ":        ";
					}
					else if (j == n - 1) {
						cout << a[i][j] << " ";
					}
					else {
						cout << a[i][j] << ",        ";
					}
				}
				cout << "\n";
			}

			cout << "\nSolution:\n";
			for (int i = 0; i < n; i++) {
				for (int j = n; j < n * 2; j++) {
					cout << a[i][j] << "    ";
				}
				cout << "\n";
			}

			//write inverse file
			ofstream inverseFile;
			inverseFile.open("Inverse.txt");
			for (int i = 0; i < n; i++) {
				for (int j = n; j < 2 * n; j++) {
					if (j < 2 * n - 1) {
						inverseFile << a[i][j] << ",";
					}
					else {
						inverseFile << a[i][j];
					}
				}
				inverseFile << "\n";
			}
			inverseFile.close();
		}
		else {
			cout << "Unable to compute the inverse of a matrix not of the form (n x n).\n";
			// stop the program
			exit(1);
		}
	}
	/***********************Solving linear equations method***********************/
	else if (matrixType == 2) {
		cout << "Please ensure the input file is the matrix plus the right hand side of the equation as the final column";
		int columns = rowSize - 1;
		int rows = a.size();

		//print out augmented matrix
		cout << "\nAugmented Matrix:\n";
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns + 1; j++) {
				if (j == columns - 1) {
					cout << a[i][j] << ":        ";
				}
				else if (j == columns) {
					cout << a[i][j] << " ";
				}
				else {
					cout << a[i][j] << ",        ";
				}
			}
			cout << "\n";
		}

		//pivot matrix
		for (int i = 0; i < rows - 1; i++) {
			for (int k = 1; k < rows - i; k++) {
				if (abs(a[i][0]) < abs(a[i + k][0])) {
					for (int j = 0; j < columns + 1; j++) {
						double x = a[i + k][j];
						a[i + k][j] = a[i][j];
						a[i][j] = x;
					}
				}
			}
		}
		//ensure diagonal is non zero
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns + 1; j++) {
				if (a[i][i] == 0) {
					if (i != 0) {
						a[i][j] = a[i][j] + a[i - 1][j];
					}
					else {
						a[i][j] = a[i][j] + a[i + 1][j];
					}
				}
			}
		}

		//print out pivoted matrix
		cout << "\npivoted output:\n";
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns + 1; j++) {
				if (j == columns - 1) {
					cout << a[i][j] << ":        ";
				}
				else if (j == columns) {
					cout << a[i][j] << " ";
				}
				else {
					cout << a[i][j] << ",        ";
				}
			}
			cout << "\n";
		}


		//reduce to echelon matrix
		for (int i = 0; i < rows; i++) {
			for (int k = 1; k < rows; k++) {
				if (k > i) {
					double b = a[k][i] / a[i][i];
					for (int j = 0; j < columns + 1; j++) {
						a[k][j] = a[k][j] - b*a[i][j];
					}
				}
			}
		}
		//reduce to echelon by making diagonals 1
		for (int i = 0; i < rows; i++) {
			double x = a[i][i];
			for (int j = 0; j < columns + 1; j++) {
				a[i][j] = a[i][j] / x;
			}
		}

		//print out echelon matrix
		cout << "\nechelon matrix:\n";
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns + 1; j++) {
				if (j == columns - 1) {
					cout << a[i][j] << ":        ";
				}
				else if (j == columns) {
					cout << a[i][j] << " ";
				}
				else {
					cout << a[i][j] << ",        ";
				}
			}
			cout << "\n";
		}


		//do back substitution 
		for (int i = rows - 1; i >= 0; i--) {
			for (int k = rows - 1; k >= 0; k--) {
				if (k < i) {
					double b = a[k][i] / a[i][i];
					for (int j = 0; j < columns + 1; j++) {
						a[k][j] = a[k][j] - b*a[i][j];
					}
				}
			}
		}

		//round answer to zero for very small values
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns + 1; j++) {
				if (abs(a[i][j]) < TOLERANCE) {
					a[i][j] = 0;
				}
			}
		}

		//print out diagonalized matrix
		cout << "\ndiagonalized matrix:\n";
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns + 1; j++) {
				if (j == columns - 1) {
					cout << a[i][j] << ":        ";
				}
				else if (j == columns) {
					cout << a[i][j] << " ";
				}
				else {
					cout << a[i][j] << ",        ";
				}
			}
			cout << "\n";
		}

		cout << "\nSolutions:\n";
		for (int i = 0; i < rows; i++) {
			for (int j = columns; j < columns + 1; j++) {
				cout << a[i][j] << "    ";
			}
			cout << "\n";
		}

		//write inverse file
		ofstream inverseFile;
		inverseFile.open("Inverse.txt");
		for (int i = 0; i < rows; i++) {
			for (int j = columns; j < columns + 1; j++) {
				inverseFile << a[i][j];
			}
			inverseFile << "\n";
		}
		inverseFile.close();
	}
}