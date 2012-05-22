#ifndef DATAMANIPULATION_H
#define DATAMANIPULATION_H

#include <iostream>

using namespace std;

namespace DataM{
	string getUserInput ();					//gets the user input.
	string subInput (string);				//generate the separate sentences in the user input.
	string rmSubInput (string);				//remove the sentences that were already calculate from the input.
	string	delSpaces (string);				//delete spaces in the user input.
	string insMult (string);				//If there aren't any operators before a parentheses, add a multiplication sign in this position.
	string justParentheses(string);				//Return a string with the sequence of the parentheses, for a parentheses closure check.
	double stringToDouble (string,int,int);			//typecast the string numbers to double for operation.
}

#endif
