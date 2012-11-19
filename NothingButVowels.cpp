/* File: NothingButVowels.cpp
 * Author: Billy Meyers
 * Date: February 7, 2012
 * ---------------
 * This program was inspired by today's Dilbert comic. In the strip, Dilbert's email
 * program has a problem such that every email he sends has nothing but vowels.
 * This program can be used to help translate the garbled emails back into their 
 * original meaning. The program takes a string of vowels as input as well as the 
 * length of the desired word and prints out all the words in the lexicon of that 
 * length that contain the given vowel pattern.
 *
 * It turns out that this program is not too useful, though. For example, there are 
 * over 2,000 English words with the vowel pattern 'a'. So there needs to be more
 * steps to filter the results such that they are useful.
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "lexicon.h"
#include "vector.h"
#include "map.h"
#include "set.h"
using namespace std;

/* Function Prototypes */
void CreateVowelMap(Lexicon words, Map<string, Vector<Set<string> > > & map);
bool IsVowel(char ch);
void PrintMatches(string vowelPattern, int wordLength, Map<string, Vector<Set<string> > > map);

/* Main Program */
int main() {
	/* Create the vowel map */
	Lexicon english("lexicon.dat");
	Map<string, Vector<Set<string> > > map;
	cout << "Please wait, creating vowel map..." << endl;
	CreateVowelMap(english, map);
	cout << "Done! Size of vowel map is " << map.size() << endl;
	
	/* Get inputs from user and print matches */
	string vowelPattern;
	int wordLength = 0;
	while(true) {
		cout << "Enter vowel pattern (RETURN to quit): ";
		getline(cin, vowelPattern);
		//Future release: Error checking. Check if vowel pattern is a valid input.
		if (vowelPattern == "") break;
		wordLength = getInteger("Enter word length: ");
		cout << wordLength << " letter words with a vowel pattern of " << vowelPattern << ":" << endl;
		PrintMatches(vowelPattern, wordLength, map);
	}
	return 0;
}

/*
 * Function: CreateVowelMap
 * Usage: CreateVowelMap(map);
 * ------------------------
 * This function takes a lexicon and converts it to a vowel map. The keys for
 * vowel maps are strings, and they represent the vowel pattern of a given word. The
 * vowel pattern is the order that the vowels appear in the word (or you can think
 * of it as the word with the consonants removed). The values in the vowel map are
 * vectors. Each vector index contains a set of strings that have the vowel pattern
 * in the given key-value pair. The number of letters in the word coincide with the 
 * index of the vector. 
 */
void CreateVowelMap(Lexicon words, Map<string, Vector<Set<string> > > & map) {
	foreach (string word in words) {
		int len = word.length();
		
		/* Get vowel pattern for current word */
		string vowelPattern;
		for (int i=0; i<len; i++)
			if (IsVowel(word[i])) vowelPattern += word[i];
		
		/*If the vowel pattern is already in the map, add word to the set at the 
		 *index of the vector that corresponds to the length of the word. If the 
		 *vector is too small, add a bunch of empty sets until it is big enough
		 */
		if (map.containsKey(vowelPattern)) {
			if (map[vowelPattern].size()<=len) {
				for (int i=0; i<=(len+5-map[vowelPattern].size()); i++) {
					Set<string> set;
					map[vowelPattern].add(set);
				}
			}
			map[vowelPattern][len].add(word);
		}

		/* Otherwise if the vowel pattern isn't in the map, add it to the map */
		else {
			Set<string> set;
			set.add(word);
			Vector<Set <string> > matches(len+1);
			matches[len] = set;
			map.put(vowelPattern, matches);
		}
	}
}

/*
 * Function: IsVowel
 * Usage: if IsVowel(ch) //do something
 * ------------------------
 * This function takes a given char and checks if it is a vowel.
 */
bool IsVowel(char ch) {
	return (ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u');
}

/*
 * Function: PrintMatches
 * Usage: PrintMatches("a", 5, map);
 * ------------------------
 * This function prints out all the words of length wordLength with the vowel pattern
 * of vowelPattern that appear in a given vowel map.
 */
void PrintMatches(string vowelPattern, int wordLength, Map<string, Vector<Set<string> > > map) {
	Set<string> matchingSet = map[vowelPattern][wordLength];
	foreach (string word in matchingSet) cout << word << endl;
	cout << "Found " << matchingSet.size() << " matches!" << endl;
}
