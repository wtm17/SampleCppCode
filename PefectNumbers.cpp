/*
 * File: PerfectNumbers.cpp
 * ------------------------
 * Greek mathematicians defined a perfect number as a number which
 * is equal to the sum of its proper divisors. This program lists
 * all the perfect numbers within a given range.
 */

#include <iostream>
using namespace std;

/* Constants */

const int MIN_RANGE = 1; /* Minimum of range to find perfect numbers */
const int MAX_RANGE = 10000; /* Maximum of range to find perfect numbers */

/* Function prototype */

bool IsPerfect(int n); 

/* Main program */

int main() {
	cout << "This program lists all perfect numbers between " << MIN_RANGE << " and " << MAX_RANGE << "." << endl;
	for (int i=MIN_RANGE; i<=MAX_RANGE; i++)
		if (IsPerfect(i)) cout << i << endl;
	return 0;
}

/*
 * Function: IsPerfect
 * Usage: if(IsPerfect(n)) //do something
 * ------------------------
 * Returns true if the number is perfect. A perfect number is defined as
 * a number which is the sum of its proper divisors. For example, 6 is a
 * perfect number because it is the sum of 1, 2, and 3.
 */

bool IsPerfect(int n) {
	int sum = 1;
	for (int i=2; i<=n/2; i++) {
		if (n%i==0) sum += i;
	}
	return sum==n;
}