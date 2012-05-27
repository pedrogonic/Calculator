#ifndef MEMORYHANDLING_H
#define MEMORYHANDLING_H

#include <iostream>

using namespace std;

struct my_var{
	string nm;				//name of the variable.
	string val;				//value of the cariable.
	struct my_var *prev;			//reference to the previous variable in the variable list.
};

namespace Mem{
	int open();				//Function to open the Calculator, creating the head. Returns a success code.
	int clear();				//Function to clear all the variables in the memory, except the head. Returns a success code.
	int add(string, string);		//Function to add a new variable to the memory. Returns a success code.
	string search(string);			//Function to search the memory for the asked variable. It receives the name of the variable and returns the value. If the value == "error", not found. 
	int close();				//Function to close the Calculator, which calls the clear funciton then deletes the head. Returns a success code.
}

#endif
