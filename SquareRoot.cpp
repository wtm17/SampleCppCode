/*
 * File: SquareRoot.cpp
 * --------------------
 * This program recursively calculates the square root of a number to the precision
 * of up to four decimal places.
 */

#include <iostream>
using namespace std;

const double PRECISION = .00001;

double squareRoot(double d);
double recursiveSquareRoot(double d, double low, double high, double increment);

int main() {
	double square = 0;
	cout << "This program calculates the square root of a number." << endl;
	cout << "Enter number: ";
	cin >> square;
	cout << "The square root of " << square << " is " << squareRoot(square) << endl;
	return 0;
}

double squareRoot(double d) {
	return recursiveSquareRoot(d, 0, d, 1.0);
}


double recursiveSquareRoot(double d, double low, double high, double increment) {
	double newlow = low;
	double newhigh = high;

	for (double i = low; i < high; i += increment) {
		if (i*i == d) {
			return i;
		}
		if (i*i > d) {
			newhigh = i;
			break;
		}
		newlow = i;
	}

	if (increment == PRECISION) {
		if (((int)((1/PRECISION)*newlow)) % 10>=5) return high;
		else return low;
	}

	return recursiveSquareRoot(d, newlow, newhigh, increment/10);
}