
/* File: SolveCryptoquip.cpp
 * Author: Billy Meyers
 * Date: February 11, 2012
 * ---------------
 * This program is the first step for solving Cryptoquip puzzles.
 *
 * A Cryptoquip is a pun which has been encrypted with a letter substitution cypher, 
 * i.e. A=D, F=J, etc. They can often be found in your daily newspaper. This solution
 * uses the concept that each word has a letter code, which is simply the pattern of 
 * letters that have been changed to numbers. For example, the letter code for 'that' is
 * 0120 and the letter code for 'letter' is 012213. 
 *
 * Currently, this program only does 3 things:
 * 
 *   1. Takes a lexicon of English words and creates a Map of letter codes and all of the 
 *	    words that match that letter code.
 *	 2. Asks for a word as input. 
 *   3. Prints out the letter code for that word as well as the number of words that have 
 *      the same letter code as the input string.
 *
 * This is only a first step in solving the cryptoquip problem. More work still needs to
 * be done.
 */

#include <iostream>
#include <string>
#include "map.h"
#include "set.h"
#include "lexicon.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

void CreateLetterCodeMap(Lexicon words, Map<string, Set<string> > &map);
string GetLetterCode(string str);

int main() {
	Map<string, Set<string> > LetterCodeMap;
	Map<char, char> SolutionKey;

	//Create the Letter Code Map from the Lexicon
	Lexicon english("lexicon.dat");
	cout << "Please wait, building letter code map..." << endl;
	CreateLetterCodeMap(english, LetterCodeMap);
	cout << "Done! Map contains " << LetterCodeMap.size() << " letter codes." << endl << endl;
	

	while (true) {
		string str = getLine("Enter string: ");
		if (str=="") break;
		string code = GetLetterCode(str);
		cout << "The letter code for " << str << " is " << code << "." << endl;
		cout << "Number of words with this letter code: ";
		cout << LetterCodeMap[code].size();
		cout << endl;
	}

	return 0;
}

/*
 * Function: CreateLetterCodeMap
 * Usage: CreateLetterCodeMap(words, map);
 * ------------------------
 * This function takes a lexicon and populates a given Map<string, Set<string> > with
 * all of the letter codes in the lexicon. The keys in the Letter Code map are strings
 * of numbers, which are the letter codes (ie 011, 012, 011221, etc). The values are sets
 * of strings, which are all the words in the lexicon that have the given letter code. For
 * example, 011 would have all, too, inn, etc. 
 */
void CreateLetterCodeMap(Lexicon words, Map<string, Set<string> > &map) {
	foreach (string word in words) {
		string code = GetLetterCode(word);

		//If the code is already in the map, add word to the set which corresponds 
		//to the code.
		 
		if (map.containsKey(code)) {
			map[code].add(word);
		}

		/* Otherwise if the code isn't in the map, add it to the map */
		else {
			Set<string> set;
			set.add(word);
			map.put(code, set);
		}
	}
}

/*
 * Function: GetLetterCode
 * Usage: string code = GetLetterCode(str);
 * ------------------------
 * This function takes a string as a parameter and returns the associated letter code. 
 */
string GetLetterCode(string str) {
	string result; 
	int counter = 0;
	result += integerToString(counter);

	for (int i=1; i<str.length(); i++) {
		int found = str.substr(0,i).find(str[i]);
		if (found!=string::npos) {
			result += result[found];
		} else {
			counter ++;
			result += integerToString(counter);
		}
	}

	return result;
}