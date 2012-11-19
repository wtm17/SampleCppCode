/* File: CreateCryptoquip.cpp
 * Author: Billy Meyers
 * Date: October 30, 2012
 * ---------------
 * This program creates a Cryptoquip from a given input string.
 *
 * A Cryptoquip is a pun which has been encrypted with a letter substitution cypher, 
 * i.e. A=D, F=J, etc. They can often be found in your daily newspaper. 
 */


#include <iostream>
#include <string>
#include <cctype>

#include "map.h"
#include "set.h"
#include "simpio.h"
#include "random.h"
using namespace std;

string CreateCryptoquip(string str, Map<char, char> &key, Set<char> &used);
string printhint(string str, Map<char, char> key);

int main() {
	
	Map<char, char> SolutionKey;
	Set<char> UsedValues;
	
	while (true) {
		string str = getLine("Enter solution: ");
		if (str=="") break;
		string cryptoquip = CreateCryptoquip(str, SolutionKey, UsedValues);
		cout << "Here is the puzzle: " << endl;
		cout << cryptoquip << endl;
		cout << "Hint: " << printhint(cryptoquip, SolutionKey) << endl;
	}
	
	return 0;
}

/*
 * Function: CreateCryptoquip
 * Usage: string cryptoquip = CreateCryptoquip(str, SolutionKey, UsedValues);
 * ------------------------
 * This function takes a string and changes each letter to another value based
 * on a given solution key. It starts by checking if the current letter is already
 * in the solution key. If not, it assigns a random letter to it and puts them into
 * the solution key. If so, it changes the letter to the letter in the solution key.
 * Two different letters cannot be assigned to the same letter; thus, the Set parameter
 * keeps track of the letters that have already been assigned (the values of in the map). 
 */
string CreateCryptoquip(string str, Map<char, char> &key, Set<char> &used) {
	for (int i=0; i<str.length(); i++) {
		char current = str[i];
		if isalpha(current) {				//checks if it's a letter
			if (!map.containsKey(current)) {
				char value;
				while (true) {
					int n = randomInteger(1,25);
					value = 'A' + n;
					if !used.contains(value) break;
				}
				key.put(current, value);
			}
			str[i] = map[current];
		}
	}
	return str;
}

/*
 * Function: printhint
 * Usage: printhint(cryptoquip, SolutionKey);
 * ------------------------
 * This function prints a solution hint to a puzzle. The hint is 
 * determined by the following method:
 *
 *	1. Look for a letter that occurs 3 times
 *	2. Look for a letter that occurs 4 times
 *	3. Look for a letter that occurs twice
 *  4. If none of the above, then just print the first letter in the puzzle
 *	   as the hint.
 */
string printhint(string puzzle, Map<char, char> key) {
	string hint;

	for (int i=0; i<puzzle.length(); i++) {
		int counter = 0;
		char current = puzzle[i];
		for (int j=0; j<puzzle.length(); j++) {
			if current == puzzle[j]
				counter++;
		}
		if counter == 3 {
			hint = current + " = " + key[current];
			return hint;
		}	
	}

	for (int i=0; i<puzzle.length(); i++) {
		int counter = 0;
		char current = puzzle[i];
		for (int j=0; j<puzzle.length(); j++) {
			if current == puzzle[j]
				counter++;
		}
		if counter == 4 {
			hint = current + " = " + key[current];
			return hint;
		}	
	}

	for (int i=0; i<puzzle.length(); i++) {
		int counter = 0;
		char current = puzzle[i];
		for (int j=0; j<puzzle.length(); j++) {
			if current == puzzle[j]
				counter++;
		}
		if counter == 2 {
			hint = current + " = " + key[current];
			return hint;
		}	
	}

	hint = puzzle[0] + " = " + key[puzzle[0]];
	return hint;
}
*/

